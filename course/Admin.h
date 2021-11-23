#pragma once 
#include <string>

#include "User.h"
#include "DataBase.h"

/* TODO 
	1) ����������� ���������� ��������� � ����������� ����� �������������
*/


/*----------------Class Admin--------------------*/
class Admin : public User{
private:
	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass, L"") { ; }

	vector<Student*> getStudents2V();
	vector<User*> getUsers2V();

	int AddUser();
	int DelUser(User * s);

	int AddStudent();
	int DelStudent(User * s);
};