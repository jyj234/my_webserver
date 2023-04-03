#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"
#include "time_heap.h"
#include "MysqlDB.h"
#include "userdata.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000
#define PRINT_INTPUT_ERROR printf( "usage: %s [-t thread_number] [-p port_number]\n", basename( argv[0] ) )

extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );
extern int setnonblocking(int fd);
static int sig_pipefd[2];

//MysqlDB<userdata>* MysqlDB<userdata>::instance=NULL;
time_heap* time_heap::instance=NULL;
time_heap* http_conn::m_time_heap=time_heap::get_heap(MAX_FD);
void sig_del_inactive_connection(int sig){
	int save_errno = errno;
    	int msg = sig;
    	send( sig_pipefd[1], ( char* )&msg, 1, 0 );
    	errno = save_errno;
}
void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void show_error( int connfd, const char* info )
{
    printf( "%s", info );
    send( connfd, info, strlen( info ), 0 );
    close( connfd );
}

void del_connection(){
	time_heap::get_heap()->tick();
	alarm(TIMESLOT);
}
int main( int argc, char* argv[] )
{
    int parse_n=1;
    int port=80;
    int thread_number=8;
	while(parse_n<argc&&argv[parse_n][0]=='-'){
		switch (argv[parse_n][1]){
			case 't':thread_number=atoi(argv[++parse_n]);
				 break;
			case 'p':port=atoi(argv[++parse_n]);
				 break;
			default:
				PRINT_INTPUT_ERROR;
				return 1;	
		}
		parse_n++;

	}
   // int port = atoi( argv[parse_n] );
   // addsig( SIGPIPE, SIG_IGN );
    	threadpool< http_conn >* pool=threadpool<http_conn>::getpool(thread_number);
    http_conn* users = new http_conn[ MAX_FD ];
    assert( users );

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    assert( listenfd >= 0 );
    struct linger tmp = { 1, 0 };
    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons( port );

    ret =bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret >= 0 );

    ret = listen( listenfd, 5 );
    assert( ret >= 0 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create( 5 );
    assert( epollfd != -1 );
    ret = socketpair( PF_UNIX, SOCK_STREAM, 0, sig_pipefd );
    assert( ret != -1 );
    setnonblocking( sig_pipefd[1] );
    addfd( epollfd, sig_pipefd[0],false );
    addfd( epollfd, listenfd, false );
    http_conn::m_epollfd = epollfd;
	addsig(SIGALRM,sig_del_inactive_connection,false);
    bool timeout=false;
    alarm(TIMESLOT);

    MysqlDB<userdata>* db=MysqlDB<userdata>::getMysqlDB();
    db->connect( "localhost", "root", "root@123", "user" ); 
   // int http_conn::tmp=1;
   // printf("%d\n",http_conn::tmp);
    while( true )
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;
            if( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd = accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
                if ( connfd < 0 )
                {
                    printf( "errno is: %d\n", errno );
                    continue;
                }
                if( http_conn::m_user_count >= MAX_FD )
                {
                    show_error( connfd, "Internal server busy" );
                    continue;
                }
               //printf("user_count=%d\n",http_conn::m_user_count); 
                users[connfd].init( connfd, client_address );

            }
	    else if (( sockfd == sig_pipefd[0] ) && ( events[i].events & EPOLLIN )){
		timeout=true;

	    }
            else if( events[i].events & ( EPOLLRDHUP | EPOLLHUP | EPOLLERR ) )
            {
                users[sockfd].close_conn();
		printf("close\n");
            }
            else if( events[i].events & EPOLLIN )
            {
                if( users[sockfd].read() )
                {
                    pool->append( users + sockfd );
                }
                else
                {
                    users[sockfd].close_conn();
		    printf("read error\n");
                }
            }
            else if( events[i].events & EPOLLOUT )
            {
                if( !users[sockfd].write() )
                {
                    users[sockfd].close_conn();
		    printf("write error\n");
                }
            }
            else
	    {}
        }
	if(timeout){
	//	printf("timeslot\n");
		del_connection();
		timeout=false;
	}
    }

    close( epollfd );
    close( listenfd );
    delete [] users;
    delete pool;
    return 0;
}

