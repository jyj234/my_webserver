#ifndef MYSQLDB_H
#define MYSQLDB_H
#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;

template<typename T>
class MysqlDB {
public:
	static MysqlDB* getMysqlDB(){
		if(instance==NULL)
			instance=new MysqlDB();
		return instance;

	}
private:
	static MysqlDB* instance;

private:
	MYSQL mysql;
	MYSQL_ROW row;
	MYSQL_RES *result;
	MYSQL_FIELD *field;
public:
	MysqlDB() {
		if( mysql_init( &mysql ) == NULL ) {
			cout << "init error, line: " << __LINE__ << endl;
			exit(-1);
		}
	}
	~MysqlDB() {
		mysql_close( &mysql );
	}
	void connect( string host, string user, string passwd,  string database ) {
		if( !mysql_real_connect( &mysql, host.c_str(), user.c_str(), passwd.c_str(), 
									database.c_str(), 0, NULL, 0 ) ) {
			cout << "connect error, line: " << __LINE__ << endl;
			exit(-1);
		}
	}
	void add(string table,T userdata);
	void print_data(string table);
};
template<typename T>
MysqlDB<T>* MysqlDB<T>::instance=NULL;
 template<typename T>
 void MysqlDB<T>::add(string table,T userdata) {
                  string sql = "insert into "+table+" values"+userdata.getdata()+";";
		  //('" + id + "', '" + email +
                   //                               "', '" + password + "');";
 
                  cout<<sql<<endl;
                  mysql_query( &mysql, sql.c_str() );
          result = mysql_store_result( &mysql );
         /* if( !result ) {
                  cout << "result error, line : " << __LINE__ << endl;
                  cout<<mysql_errno(&mysql)<<" "<<mysql_error(&mysql)<<endl;
                  return ;
          }*/
  }
  template<typename T>
  void MysqlDB<T>::print_data(string table) {
 
          // string sql = "select * from info where name = '" + name + "';";  //要有''
          string sql = "select * from "+table+";";
          mysql_query( &mysql, sql.c_str() );
 
          result = mysql_store_result( &mysql );
          if( !result ) {
                  cout << "result error, line : " << __LINE__ << endl;
                  cout<<mysql_errno(&mysql)<<" "<<mysql_error(&mysql)<<endl;
                  return ;
          }
 
          int num;
          num = mysql_num_fields( result );  //返回字段个数
          for( int i = 0; i < num; i++ ) {
                  field = mysql_fetch_field_direct( result, i );  //返回字段类型
                  cout << field->name << "\t\t";  //输出字段名
          }
          cout << endl;
 
          while( row = mysql_fetch_row( result ), row ) {
                  for( int i = 0; i < num; i++ ) {
                          cout << row[i] << "\t\t";
                  }
                  cout << endl;
	  }
  }
     /*int main() {
     	MysqlDB db;
     	db.connect( "localhost", "root", "root@123", "user" );	
     	string table="userdata";
     db.print(table);
     db.add(table,"1","1@qq.com","1");
     db.print(table);
     return 0;
     }*/      
#endif   
