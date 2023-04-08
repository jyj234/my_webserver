#ifndef USERDATA_H
#define USERDATA_H
#include<iostream>
#include<map>
class userdata{
private:
	std::map<std::string,std::string> data;
public:
	void parse(char* content){
		char* name=content,*value=NULL,*tmp=NULL;
		while(name&&(value=strpbrk(name,"="))){
			*value++='\0';
			tmp=strpbrk(value,"&");
			if(tmp)
			*tmp++='\0';
			data[name]=value;
			name=tmp;	
		}
	}
	std::string get_mysql(){
		std::string sql="(";
		for(auto it:data){
			if(it.first!=(*data.begin()).first)
				sql+=",";
			sql+="'"+it.second+"'";
		}
		sql+=")";
		return sql;
	}
	void remove(std::string s){
		data.erase(s);
		return;
	}
	std::string get(const std::string& name){
		return data[name];
	}
};
#endif
