#pragma once 
#include <string>
#include <map>

#include "User.h"
#include "DataBase.h"
#include "AbstractHandler.h"


/*----------------Class Admin--------------------*/
class Admin : public User{
private:
	//zfriend float Student::getStipendRatio(float avg_mark);
	//friend int Student::calcCourse(wstring student_id);

	void mergeStGr(vector<Student *> *, const map<wstring, vector<wstring>>, wstring mode);
	vector<int> addMarks2V(wstring student_id, int course, vector<wstring> subjs, int term = 0);
	int getGroupExample(int group);

public:
	Admin() { ; }
	Admin(std::wstring login, std::wstring pass) : User(login, pass, L"") { ; }

	/*-----Admin------*/
	int AddUser();
	vector<User*> getUsers();
	vector<User *> getFullUser();
	int DelUser(User * s);
	int	EditUser(User * s);
	/*-----Admin------*/

	/*-----Student------*/
	int AddStudent();
	int DelStudent(Student * s);

	pair<wstring, wstring> EnterFIO();
	Faculty * EnterFaculty();
	Speciality * EnterSpec(Faculty faculty);
	Group * EnterGroup(Faculty faculty, Speciality spec);
	int EnterEdForm();

	vector<Student*> getStudents(wstring student_id = L"");
	int AddMarksToStudent(Student *s, int term = 0);
	int AddMarksToStudent(wstring student_id, int term = 0);
	int AddStipendToStudent(Student *s);
	int AddStipendToStudent(wstring student_id);

	int EditMarks(Student *, int);

	int setStipendToStudent(Student *, Stipend *);
	int delStipendToStudent(Student *);
	/*-----Student------*/

	int AddAdditionalStipend();
	int DelStipend(Stipend *);
};