#pragma once 
#include <string>
#include <map>

#include "User.h"
#include "DataBase.h"



/*----------------Class Admin--------------------*/
class Admin : public User{
private:
	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);

	std::map<std::wstring, float> rate = {
		{L"base", 96.4 },
		{L"min", 1.2 },
		{L"middle", 1.4 },
		{L"max", 1.6} };

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass, L"") { ; }

	/*-----Admin------*/
	int AddUser();
	vector<User*> getUsers2V();
	int DelUser(User * s);
	/*-----Admin------*/

	/*-----Student------*/
	int AddStudent();
	int DelStudent(Student * s);
	vector<Student*> getStudents2V();
	int AddMarksToStudent(Student *s);
	int AddMarksToStudent(wstring student_id);
	/*-----Student------*/
};