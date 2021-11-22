#pragma once 
#include "Student.h"

/*----------------Class User--------------------*/

/* TODO
	user может просматривать ифнормацию о студенте, (менять ФИО он не может). 
	КРч он может только просматривать инфу.

	В студенте реализовать ф-ю которая примнимает что-то с оценкми и засовывет их в во что-то типо map or vector
*/


class User {
private:
	std::wstring login;
	std::wstring password;

	Student student;

public:
	User() { ; }
	User(std::wstring login, std::wstring pass) : login(login), password(pass) { ; }
	User(const User &);

	
	std::wstring getLogin() { return login; }
	std::wstring getPassword() { return password; }

	void setLogin(std::wstring login) { this->login = login; }
	void setPassword(std::wstring pass) { this->password = pass; }
};