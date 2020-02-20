#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User
{
	private:
		
		std::string userName;
		std::string passWord;
	public:
		User();
		User(std::string user, std::string pass);
		~User();
		std::string getPass();
		std::string getName();
};
#endif

