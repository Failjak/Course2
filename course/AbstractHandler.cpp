#include "AbstractHandler.h"
#include <algorithm>

namespace AbstractHandler
{
		/*─────Comparatros─────*/
	bool compByAvgMark(Student * s1, Student * s2)
	{
		return s1->getAvgMark() > s2->getAvgMark();
	}

	
		/*─────Comparatros─────*/

	int choice_column(vector<wstring> columns)
	{
		bool flag = true;
		wstring choice;
		int i = 0;

		for (auto col : columns)
			wcout << ++i << L") " << col << endl;
		wcout << L" Ваш выбор: ";

		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"2") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	void StudentRating(vector<Student *> students, vector<wstring> fac_spec_group)
	{
		if (fac_spec_group.size() != 3) { wcout << L"Неверный параметры"; return; }
		vector<Student *> req_stud;

		for (auto stud : students)
		{
			if (stud->getFaculty() == fac_spec_group.at(0) and
				stud->getSpec() == fac_spec_group.at(1) and
				stud->getGroup() == fac_spec_group.at(2)) {	req_stud.push_back(stud); }
		}
		sort(req_stud.begin(), req_stud.end(), compByAvgMark);
		
		pprintStudentRating(req_stud);
	}

	void pprintStudentRating(vector<Student *> students)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		int max_size_id = 0,  max_size_avg_mark = 0;

		for (int i = 0; i < students.size(); i++)
		{
			if (to_string(students.at(i)->getAvgMark()).length() > max_size_avg_mark)
				max_size_avg_mark = to_string(students.at(i)->getAvgMark()).length();

			if (students.at(i)->getStudentId().length() > max_size_id)
				max_size_id = students.at(i)->getStudentId().length();
		}

		int table_width = space_subjects + (
			(max_size_avg_mark > MIN_SPACE ? max_size_avg_mark + 1 : MIN_SPACE) +
			(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE));


		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";
		SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);

		wcout
			<< setw(5) << left << L"№"
			<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << L"ID"
			<< setw(max_size_avg_mark > MIN_SPACE ? max_size_avg_mark + 1 : MIN_SPACE) << left << L"Ср. балл";


		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << L"│" << endl;

		for (int j = 0; j < students.size(); j++) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│"
				<< setw(5) << j + 1
				<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << students[j]->getStudentId()
				<< setw(max_size_avg_mark > MIN_SPACE ? max_size_avg_mark + 1 : MIN_SPACE) << left << students[j]->getAvgMark()
				<< left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}
}
