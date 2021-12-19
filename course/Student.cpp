#include "Student.h"
#include "Header.h"


Student::Student(const Student & tmp) : People(tmp.name, tmp.surname, tmp.patronomic)
{
	this->student_id = tmp.student_id;
	this->group = tmp.group;
	this->faculty = tmp.faculty;
	this->spec = tmp.spec;
	this->email = tmp.email;
	this->phone = tmp.phone;
	this->education_form = tmp.education_form;
	this->marks = tmp.marks;
	this->course = tmp.course;
	for (auto s : tmp.addit_stipend)
		this->addit_stipend.push_back(new Stipend(*s));
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


float Student::getStipendLastTerm()
{
	if (stipend.size())
	{
		return stipend.back().second;
	}
	return -1;
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

float Student::getStipendRatio(float avg_mark)
{
	using namespace StipendConsts;
	float stipend_ratio = -1;
	wstring key;

	for (auto it = stipend_condition.begin(); it != stipend_condition.end(); ++it)
	{
		if ((*it).second.first <= avg_mark and avg_mark <= (*it).second.second)
		{
			key = (*it).first;
			return stipend_rate.at(key);
		}
	}
	return stipend_ratio;
}

void Student::calcStipend(Student * s)
{
	using namespace StipendConsts;

	if (!s->getEdFormInt()) { return; }

	vector<pair<int, float>> stipend;

	vector<pair<pair<int, bool>, float>> marks = s->getAvgMarkByTerm(); // schema: {{ {term, retake}, {marks...} }}	
	vector<pair<pair<int, bool>, float>>::iterator mark;
	vector<pair<pair<int, bool>, float>>::iterator prev_mark;

	for (mark = marks.begin(), prev_mark = marks.begin(); mark != marks.end(); prev_mark = mark, mark++)
	{
		if ((*mark).first.first == 1) { stipend.push_back(make_pair(1, StipendConsts::BASE_STIPEND)); continue; }  // add stipend for the first semester

		float avg_mark = (*prev_mark).second;
		float ratio = getStipendRatio(avg_mark);

		if ((*prev_mark).first.second) { stipend.push_back(make_pair(1, 0)); continue; } // пересдача

		stipend.push_back(make_pair((*mark).first.first, BASE_STIPEND * ratio));
	}

	for (auto stip : s->getAdditStipend())
		for (auto main_stip = stipend.begin(); main_stip != stipend.end(); main_stip++)
			if ((*main_stip).first >= stip->getTerm())
				(*main_stip).second += stip->getRatio() * StipendConsts::MIN_LIVING_STANDART;

	s->setStipend(stipend);
}