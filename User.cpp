#include "User.h"

User::User()
{
	userName= "";
	passWord= "";
}

User::User(std::string user, std::string pass)
{
	userName= user;
	passWord= pass;
}

User::~User()
{
}

std::string User::getPass()
{
	return passWord;
}

std::string User::getName()
{
	return userName;
}
