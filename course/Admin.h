#pragma once 
#include <string>

#include "User.h"

/* TODO 
	1) ����������� ���������� ��������� � ����������� ����� �������������
*/


/*----------------Class Admin--------------------*/
class Admin : public User{
private:

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass) { ; }
};