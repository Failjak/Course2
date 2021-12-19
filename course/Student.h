#pragma once
#include <map>
#include <vector>
#include <string>

#include "Stipend.h"
#include "Faculty.h"
#include "Speciality.h"
#include "Group.h"
#include "People.h"

using namespace std;

class Admin;

/*----------------Class Student--------------------*/
class Student : public People {
private:
	map<int, map<wstring, int>> marks; // term: (subj: {mark, ...})
	wstring student_id;
	wstring email;
	wstring phone;
	wstring education_form;
	int course;

	Group group;
	Speciality spec;
	Faculty faculty;

	vector<Stipend*> addit_stipend;
	vector<pair<int, float>> stipend; // schema: { {term, stipend} }

	float getStipendRatio(float avg_mark);

public:
	Student() {}
	Student(wstring student_id, wstring first_name, wstring last_name, wstring patr, Group group,
		Faculty faculty, Speciality spec, wstring email, wstring phone, wstring ed_form) :
		student_id(student_id), group(group), faculty(faculty), spec(spec), email(email), phone(phone), education_form(ed_form),
		People(first_name, last_name, patr) { ; }
	Student(const Student &);


	void setStudentId(wstring id) { student_id = id;}

	void setGroup(Group g) { group = g; }
	void setGroup(wstring g) { group.setName(g); }
	void setFaculty(Faculty f) { faculty = f; }
	void setFaculty(wstring abbrev) { faculty.setAbbrev(abbrev); }
	void setSpec(Speciality s) { spec = s; }
	void setSpec(wstring s) { spec.setAbbrev(s); }

	void setEmail(wstring m) { email = m; }
	void setPhone(wstring p) { phone = p; }
	void setEdForm(wstring ed_form) { education_form = ed_form; }
	void setEdForm(int ed_form) { education_form = ed_form == 1 ? L"F" : L"C"; }
	void setMarks(vector<pair<pair<int, bool>, vector<int>>>, vector<wstring> subj);
	void setStipend(vector<pair<int, float>> stipend) { this->stipend = stipend; }
	void setCourse(int course) { this->course = course; }
	void setAdditStipdends(vector<Stipend *> stipends) { this->addit_stipend = stipends; }


	wstring getStudentId() { return student_id; }
	Group getGroup() { return group; }
	Faculty getFaculty() { return faculty; }
	Speciality getSpec() { return spec; }
	wstring getEmail() { return email; }
	wstring getPhone() { return phone; }
	vector<pair<int, float>> getStipend() { return stipend; }
	float getStipendLastTerm();
	int getCourse() { return course; }
	vector<Stipend* > getAdditStipend() { return addit_stipend; }

	wstring getEdFormWstr() { return education_form == L"F" ? L"Бюджет" : L"Платное"; }
	wstring getEdForm() { return education_form; }
	int getEdFormInt() { return education_form == L"F" ? 1 : 0; } //if f -> 1, else -> 0

	vector<pair<pair<int, bool>, float>> getAvgMarkByTerm();
	float getAvgMark();
	map<int, map<wstring, int>> getMarks() { return marks; }


	/*-----friend class Admin-----*/
	friend class Admin;
	/*----- ----- -------- -- ---- -----*/

	void calcStipend(Student *s);
	void printRole() { wcout << L"Student" << endl; }
};