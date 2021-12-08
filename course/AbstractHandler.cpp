//#include "AbstractHandler.h"
//
//void AbstractHandler::pprintMark(vector<Student*>, wstring)
//{
//}
//
//void AbstractHandler::pprintStipend(vector<Student*>, wstring)
//{
//	int space_subjects = 5;
//	int MIN_SPACE = 14;
//	HANDLE hCon;
//	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	int max_size_FN = 0, max_size_id = 0, max_size_av_mark = 0, max_size_stipend = 0;
//
//	for (int i = 0; i < students.size(); i++)
//	{
//		if (students.at(i)->getStudentId().length() > max_size_id)
//			max_size_id = students.at(i)->getStudentId().size();
//
//		if (students.at(i)->getFullName().length() > max_size_FN)
//			max_size_FN = students.at(i)->getFullName().size();
//
//		if (to_string(students.at(i)->getAvgMark()).length() > max_size_av_mark)
//			max_size_av_mark = to_string(students.at(i)->getAvgMark()).length();
//
//		if (to_string(students.at(i)->getStipendLastTerm()).length() > max_size_stipend)
//			max_size_stipend = to_string(students.at(i)->getStipendLastTerm()).size();
//	}
//
//	int table_width = space_subjects + (
//		(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) +
//		(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) +
//		(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) +
//		(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE));
//
//
//	if (title.length())
//	{
//		int title_table_widht = (table_width - title.length()) / 2;
//		wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
//	}
//
//	wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
//	wcout << L"│";
//	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);
//
//	wcout
//		<< setw(5) << left << L"№"
//		<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << L"ID"
//		<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << L"ФИО"
//		<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << L"Ср. балл"
//		<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << L"Стипендия";
//
//
//	SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
//	wcout << L"│" << endl;
//
//	for (int j = 0; j < students.size(); j++) {
//		wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
//		wcout << L"│"
//			<< setw(5) << j + 1
//			<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << students[j]->getStudentId()
//			<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << students[j]->getFullName()
//			<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << std::fixed << std::setprecision(2) << students[j]->getAvgMark()
//			<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << std::fixed << std::setprecision(2) << students[j]->getStipendLastTerm()
//			<< left << L"│" << endl;
//	}
//	wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
//}
//
