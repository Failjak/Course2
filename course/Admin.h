#pragma once 
#include <string>
#include <map>

#include "User.h"
#include "DataBase.h"



/*----------------Class Admin--------------------*/
class Admin : public User{
private:
	//friend float Student::getStipendRatio(float avg_mark);
	//friend int Student::calcCourse(wstring student_id);

	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);
	vector<int> addMarks2V(wstring student_id, int course, vector<wstring> subjs);

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
	vector<Student*> getStudents2V(wstring student_id = L"");
	int AddMarksToStudent(Student *s);
	int AddMarksToStudent(wstring student_id);
	friend void Student::calcStipend(Student *s);
	/*-----Student------*/
};