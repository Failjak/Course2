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
	std::wstring student_id;
	Student student;

public:
	User() { ; }
	User(std::wstring login, std::wstring pass, std::wstring st_id) : login(login), password(pass), student_id(st_id) { ; }
	User(const User &);

	std::wstring getLogin() { return login; }
	std::wstring getPassword() { return password; }
	std::wstring getStudentId() { return student_id; }

	void setLogin(std::wstring login) { this->login = login; }
	void setPassword(std::wstring pass) { this->password = pass; }
	void setStudentId(std::wstring st_id) { this->student_id = st_id; }
	void setStudent(Student * tmp) { student = *tmp; }
};