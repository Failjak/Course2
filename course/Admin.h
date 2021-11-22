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
	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass) { ; }

	vector<Student*> getStudents2V();
	vector<User*> getUsers2V();
	int AddUser();
	int DelUser(User * s);
};