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

void Student::setMarks(vector<pair<pair<int, bool>, vector<int>>> tmp, vector<wstring> subj)
{
	/*
		tmp:	{
					{term, retake}, {Math, OOP, etc...},
					{term, retake}, {marks}
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
		tmp_marks[L"retake"] = tmp.at(i).first.second;
		marks[tmp.at(i).first.first] = tmp_marks; // key = term
	}
}


vector<pair<pair<int, bool>, float>> Student::getAvgMarkByTerm()
{
	/*
		Return avg mark by every term
		{
			{term, avg_mark},
				...
		};	
	*/

	if (!marks.size()) { return {}; }

	float avg, sum = 0;
	map<int, map <wstring, int>>::iterator iter;

	vector<pair<pair<int, bool>, float>> avg_marks; // schema: { { {term, reatake}, {marks ...} } }

	for (iter = marks.begin(); iter != marks.end(); iter++)
	{
		map <wstring, int>::iterator mark_iter;
		for (mark_iter = (*iter).second.begin(); mark_iter != (*iter).second.end(); mark_iter++)
		{
			sum += (*mark_iter).second;
		}

		pair<int, bool> term_retake = { (*iter).first, (*iter).second.at(L"retake") };

		avg_marks.push_back(make_pair(term_retake, sum / (*iter).second.size()));
		sum = 0;
	}

	return avg_marks;
}

float Student::getAvgMark()
{
	if (!marks.size()) { return 0; }

	vector<pair<pair<int, bool>, float>> avg_marks = getAvgMarkByTerm();
	float sum = 0;
	int count_subjs = 0;

	for (int i = 0; i < avg_marks.size(); i++)
	{
		sum += avg_marks.at(i).second;
	}
	return sum / avg_marks.size();
}
