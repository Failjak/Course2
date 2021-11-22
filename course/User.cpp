#include "User.h"

User::User(const User &tmp)
{
	this->login = tmp.login;
	this->password = tmp.password;
}
