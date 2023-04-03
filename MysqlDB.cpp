#include "MysqlDB.h"
template<typename T>
void MysqlDB<T>::add(string table,string id,string email,string password) {
                 string sql = "insert into "+table+" values('" + id + "', '" + email +
                                                 "', '" + password + "');";
 
                 cout<<sql<<endl;
                 mysql_query( &mysql, sql.c_str() );
         result = mysql_store_result( &mysql );
         if( !result ) {
                 cout << "result error, line : " << __LINE__ << endl;
                 cout<<mysql_errno(&mysql)<<" "<<mysql_error(&mysql)<<endl;
                 return ;
         }
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

