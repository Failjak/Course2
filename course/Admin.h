#pragma once 
#include <string>
#include <map>

#include "User.h"
#include "DataBase.h"



/*----------------Class Admin--------------------*/
class Admin : public User{
private:
	float getStipendRatio(float avg_mark);
	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);
	vector<int> addMarks2V(wstring student_id, vector<wstring> subjs);

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
	void calcStipend(Student *s);
	/*-----Student------*/
};