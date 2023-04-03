#ifndef USERDATA_H
#define USERDATA_H
#include<iostream>
class userdata{
public:
	userdata(std::string id,std::string email,std::string password):id(id),email(email),password(password){
		data="('"+id+"', '"+email+"', '"+password+"')";
	
	}
	std::string getdata(){
		return data;
	}
	void print_data(){
		std::cout<<"id="<<id<<std::endl;
		std::cout<<"email="<<email<<std::endl;
		std::cout<<"password="<<password<<std::endl;

	}
private:
	std::string id;
	std::string email;
	std::string password;
	std::string data;
};
#endif
