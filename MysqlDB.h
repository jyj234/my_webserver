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
	static int att_n;

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
	void add(string table,T& userdata);
	void print_data(string table);
	bool check(string table,T& u);
};
template<typename T>
MysqlDB<T>* MysqlDB<T>::instance=NULL;
template<typename T>
int MysqlDB<T>::att_n=3;
 template<typename T>
 void MysqlDB<T>::add(string table,T& u) {	 
                  string sql = "insert into "+table+" values"+u.get_mysql();
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
template<typename T>
bool MysqlDB<T>::check(string table,T& u)
{
	string query="select password from "+table+" where email="+"\""+u.get("email")+"\""+";"; //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
	std::cout<<query<<std::endl;
	//mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, query.c_str())){        // 执行指定为一个空结尾的字符串的SQL查询。
		cout<<"Query failed"<<endl;;
		return false;
	}
	else{
		cout<<"query success"<<endl;
	}
	//获取结果集
	if (!(result = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集
	{
		cout<<"Couldn't get resulti"<<endl;
	
		return false;
	}

	//打印数据行数
	cout<<"number of dataline returned: "<<mysql_affected_rows(&mysql)<<endl;

	//获取字段的信息
	char *str_field;  //定义一个字符串数组存储字段信息
	//for (int i = 0; i < att_n; i++)   //在已知字段数量的情况下获取字段名
	//{
		str_field = mysql_fetch_field(result)->name;	//返回一个所有字段结构的数组。
	//}
	//for (int i = 0; i < att_n; i++)   //打印字段
		printf("%10s	", str_field);

	std::cout<<endl;
	//打印获取的数据
	char** column;
	column=mysql_fetch_row(result);
	if(column&&column[0]==u.get("password"))
		return true;
	/*while ((column = mysql_fetch_row(result)))   //在已知字段数量情况下，获取并打印下一行
	{
		printf("%10s", column[0]);  //column是列数组
		cout<<endl;
	}*/
	return false;
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
