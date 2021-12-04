#pragma once 
#include "Student.h"
#include "Encryption.h"
/*----------------Class User--------------------*/

/* TODO
	user может просматривать ифнормацию о студенте, (менять ФИО он не может). 
	КРч он может только просматривать инфу.
*/


class User {
private:
	std::wstring login;
	std::wstring password;
	std::wstring student_id;
	Student student;

protected:
	int calcCourse(wstring student_id);

public:
	User() { ; }
	User(std::wstring login, std::wstring pass, std::wstring st_id) : login(login), password(Encrypt::encrypt(pass)), student_id(st_id) { ; }
	User(const User &);

	std::wstring getLogin() { return login; }
	std::wstring getEncrPassword() { return password; }
	std::wstring getPassword() { return Encrypt::decrypt(password); }
	std::wstring getStudentId() { return student_id; }
	Student * getStudent() { return &student; }

	void setLogin(std::wstring login) { this->login = login; }
	void setPassword(std::wstring pass) { this->password = Encrypt::encrypt(pass); }
	void setStudentId(std::wstring st_id) { this->student_id = st_id; }
	void setStudent(Student * tmp) { student = *tmp; }
	void setStudent();

	friend wostream& operator<<(wostream& wcout, const User & user);
};