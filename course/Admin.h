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

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass) { ; }

	vector<vector<wstring>> getUsers2V();
	bool AddUser();
};