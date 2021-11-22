#pragma once 
#include <string>

#include "User.h"
#include "DataBase.h"

/* TODO 
	1) Реализовать добавление студентов и регистрации новых пользователей
*/


/*----------------Class Admin--------------------*/
class Admin : public User{
private:

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass) { ; }

	vector<User*> getUsers2V();
	int AddUser();
	int DelUser(User * s);
};