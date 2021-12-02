#pragma once
#include <map>
#include <vector>
#include <string>

#include "People.h"

using namespace std;

/*----------------Class Student--------------------*/
class Student : public People {
private:
	map<int, map<wstring, int>> marks; // term: (subj: {mark, ...})
	wstring student_id;
	wstring group;
	wstring faculty;
	wstring spec;
	wstring email;
	wstring phone;
	wstring education_form;
	int course;

	vector<pair<int, float>> stipend; // schema: { {term, stipend} }

	float getStipendRatio(float avg_mark);

public:
	Student() { ; }
	Student(wstring student_id, wstring first_name, wstring last_name, wstring patr, wstring group,
		wstring faculty, wstring spec, wstring email, wstring phone, wstring ed_form) : 
		student_id(student_id), group(group), faculty(faculty), spec(spec), email(email), phone(phone), education_form(ed_form),
		People(first_name, last_name, patr) { ; }
	Student(const Student &);

	void setStudentId(wstring id) { student_id = id; }
	void setGroup(wstring g) { group = g; }
	void setFaculty(wstring f) { faculty = f; }
	void setSpec(wstring s) { spec = s; }
	void setEmail(wstring m) { email = m; }
	void setPhone(wstring p) { phone = p; }
	void setEdForm(wstring ed_form) { education_form = ed_form; }
	void setMarks(vector<pair<pair<int, bool>, vector<int>>>, vector<wstring> subj);
	void setStipend(vector<pair<int, float>> stipend) { this->stipend = stipend; }
	void setCourse(int course) { this->course = course; }

	wstring getStudentId() { return student_id; }
	wstring getGroup() { return group; }
	wstring getFaculty() { return faculty; }
	wstring getSpec() { return spec; }
	wstring getEmail() { return email; }
	wstring getPhone() { return phone; }
	vector<pair<int, float>> getStipend() { return stipend; }
	float getStipendLastTerm();
	int getCourse() { return course; }

	wstring getEdFormWstr() { return education_form == L"F" ? L"Бюджет" : L"Платно"; }
	wstring getEdForm() { return education_form; }
	int getEdFormInt() { return education_form == L"F" ? 1 : 0; } //if f -> 1, else 0

	vector<pair<pair<int, bool>, float>> getAvgMarkByTerm();
	float getAvgMark();
	map<int, map<wstring, int>> getMarks() { return marks; }


	/*-----friend functions to Admin-----*/
	void calcStipend(Student *s);
	/*----- ----- -------- -- ---- -----*/
};