#pragma once 
#include "Student.h"

class User {
private:
	std::wstring login;
	std::wstring password;

	Student student;

public:
	User() { ; }
	User(std::wstring login, std::wstring pass) : login(login), password(pass) { ; }

	std::wstring getLogin() { return login; }
	std::wstring getPassword() { return password; }

	void setLogin(std::wstring login) { this->login = login; }
	void setPassword(std::wstring pass) { this->password = pass; }
};