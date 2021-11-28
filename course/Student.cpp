#include "Student.h"

Student::Student(const Student & tmp)
{
	this->student_id = tmp.student_id;
	this->group = tmp.group;
	this->faculty = tmp.faculty;
	this->spec = tmp.spec;
	this->email = tmp.email;
	this->phone = tmp.phone;
	this->education_form = tmp.education_form;
}

void Student::setMarks(vector<wstring> tmp, vector<wstring> subj)
{
	//stoi(ws);
	if(tmp.size() != subj.size()) 
	{
		wcout << L"Uncorrect size in setMarks." << endl;
		return;
	}

	map <wstring, int> subj_map;

	for (int s = 1; s < subj.size(); s++)
	{
		subj_map[subj[s]] = {};
		subj_map[subj[s]] = stoi(tmp[s]);

	}
	marks[stoi(tmp[0])] = subj_map;

}

int Student::getAvgMark()
{
	if (!marks.size()) { return 0; }

	int avg, sum = 0;
	map <wstring, vector<int>>::iterator iter;

	//for (iter = marks.begin(); iter != marks.end(); iter++)
		//sum += (*iter).second.at(0); // пока берем только первую оценку
}
