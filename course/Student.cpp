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
	this->marks = tmp.marks;
}

void Student::setMarks(vector<pair<int, vector<int>>> tmp, vector<wstring> subj)
{
	/*
		tmp:	{
					term, {Math, OOP, etc...},
					term, {marks}
				};
	*/

	for (int i = 0; i < tmp.size(); i++) // get pair
	{
		map <wstring, int> tmp_marks;
		for (int j = 0; j < tmp.at(i).second.size(); j++) // get vector with marks
		{
			if (tmp.at(i).second.size() != subj.size())
			{
				wcout << L"Uncorrect size in setMarks." << endl;
				return;
			}

			tmp_marks[subj.at(j)] = tmp.at(i).second.at(j);
		}
		marks[tmp.at(i).first] = tmp_marks;
	}

	/*if(tmp.size() != subj.size()) 
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
	marks[stoi(tmp[0])] = subj_map;*/

}

vector<pair<int, float>> Student::getAvgMarkByTerm()
{
	if (!marks.size()) { return {}; }

	float avg, sum = 0;
	map<int, map <wstring, int>>::iterator iter;

	vector<pair<int, float>> avg_marks; // return avg mark by every term

	for (iter = marks.begin(); iter != marks.end(); iter++)
	{
		map <wstring, int>::iterator mark_iter;
		for (mark_iter = (*iter).second.begin(); mark_iter != (*iter).second.end(); mark_iter++)
		{
			sum += (*mark_iter).second;
		}

		avg_marks.push_back(make_pair((*iter).first, sum / (*iter).second.size()));
		sum = 0;
	}

	return avg_marks;
}

float Student::getAvgMark()
{
	if (!marks.size()) { return 0; }

	vector<pair<int, float>> avg_marks = getAvgMarkByTerm();
	float sum = 0;
	int count_subjs = 0;

	for (int i = 0; i < avg_marks.size(); i++)
	{
		sum += avg_marks.at(i).second;
	}
	return sum / avg_marks.size();
}
