#include "AbstractHandler.h"
#include "Convert.h"
#include <algorithm>

using namespace Convert;

namespace AbstractHandler
{
		/*─────Comparatros─────*/
	bool compByAvgMark(Student * s1, Student * s2)
	{
		return s1->getAvgMark() > s2->getAvgMark();
	}
	bool compByName(User * u1, User * u2)
	{
		return u1->getStudent()->getName() > u2->getStudent()->getName();
	}
	bool compBySurname(User * u1, User * u2)
	{
		return u1->getStudent()->getSurname() > u2->getStudent()->getSurname();
	}
	bool UcompByFIO(User * u1, User * u2)
	{
		auto s1 = u1->getStudent();
		auto s2 = u1->getStudent();

		if (s1->getSurname() == s2->getSurname())
		{
			if (s1->getName() == s2->getName())
				return s1->getPatronomic() > s2->getPatronomic();

			return s1->getName() > s2->getName();
		}
		return s1->getSurname() > s2->getSurname();
	}
	bool ScompByFIO(Student * s1, Student * s2)
	{
		if (s1->getSurname() == s2->getSurname())
		{
			if (s1->getName() == s2->getName())
				return s1->getPatronomic() > s2->getPatronomic();

			return s1->getName() > s2->getName();
		}
		return s1->getSurname() > s2->getSurname();
	}
		/*─────Comparatros─────*/

	int choice_column(vector<wstring> columns)
	{
		bool flag = true;
		wstring choice;
		int i = 0, mode = 0;

		if (columns.back() == L"Назад." || columns.back() == L"Назад") { mode = 1; columns.pop_back(); }

		for (auto col : columns)
			wcout << ++i << L") " << col << endl;
		if (mode) { wcout << L"0) " << L"Назад" << endl; }
		wcout << L" Ваш выбор: ";

		while (flag)
		{
			rewind(stdin);
			getline(wcin, choice);
			if (choice >= L"0" && choice <= to_wstring(columns.size())) flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	int choice_column(int columns_count)
	{
		bool flag = true;
		wstring choice;
		wcout << L" Ваш выбор: ";

		while (flag)
		{
			rewind(stdin);
			getline(wcin, choice);
			if (choice >= L"0" && choice <= to_wstring(columns_count)) flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}
	int choice_number(int max_number)
	{
		bool flag = true;
		wstring choice;

		while (flag)
		{
			rewind(stdin);
			getline(wcin, choice);
			if (choice >= L"0" && choice <= to_wstring(max_number)) flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}
	vector<User *> searchSurname(vector<User *> users, wstring surname) 
	{
		vector<User *> req_user;
		surname = ppWstring(surname);

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			size_t pos = stud->getSurname().find(surname);
			if (pos != std::string::npos)
				req_user.push_back(user);
		}

		return req_user;
	}

	int pos(const wchar_t *s, const wchar_t *c, int n)
	{
		int i, j;
		int lenC, lenS; 

		for (lenC = 0; c[lenC]; lenC++);
		for (lenS = 0; s[lenS]; lenS++);

		for (i = 0; i <= lenS - lenC; i++) {
			for (j = 0; s[i + j] == c[j]; j++); 
			if (j - lenC == 1 && i == lenS - lenC && !(n - 1)) return i;
			if (j == lenC)
				if (n - 1) n--;
				else return i;
		}
		return -1;
	}

	vector<User *> searchName(vector<User *> users, wstring name) 
	{
		vector<User *> req_user;
		name = ppWstring(name);

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			size_t pos = ppWstring(stud->getName()).find(name);
			if (pos != std::string::npos)
				req_user.push_back(user);
		}

		return req_user;
	}
	vector<User*> searchLogin(vector<User*> users, wstring login)
	{
		vector<User *> req_user;

		for (auto user : users)
		{
			size_t pos = user->getLogin().find(login);
			if (pos != std::string::npos)
				req_user.push_back(user);
		}

		return req_user;
	}
	vector<User*> searchMail(vector<User*> users, wstring mail)
	{
		vector<User *> req_user;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			size_t pos = stud->getEmail().find(mail);
			if (pos != std::string::npos)
				req_user.push_back(user);
		}

		return req_user;
	}
	vector<User*> searchPhone(vector<User*> users, wstring phone)
	{
		vector<User *> req_user;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			size_t pos = stud->getPhone().find(phone);
			if (pos != std::string::npos)
				req_user.push_back(user);
		}

		return req_user;
	}

	vector<User *> filterByEdForm(vector<User *> users, int form)
	{	
		vector<User *> req_users;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			if (stud->getEdFormInt() == form) {
				req_users.push_back(user);
			}
		}
		sort(req_users.begin(), req_users.end(), UcompByFIO);

		return req_users;
	}
	vector<User *> filterByFSG(vector<User *> users, wstring fac)
	{
		vector<User *> req_users;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			if (stud->getFaculty().getAbbrev() == fac) {
				req_users.push_back(user);
			}
		}
		sort(req_users.begin(), req_users.end(), UcompByFIO);

		return req_users;
	}
	vector<User *> filterByFSG(vector<User *> users, wstring fac, wstring spec)
	{
		vector<User *> req_users;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			if (stud->getFaculty().getAbbrev() == fac and 
				stud->getSpec().getAbbrev() == spec) {
				req_users.push_back(user);
			}
		}
		sort(req_users.begin(), req_users.end(), UcompByFIO);

		return req_users;
	}
	vector<User *> filterByFSG(vector<User *> users, wstring fac, wstring spec, wstring group)
	{
		vector<User *> req_users;

		for (auto user : users)
		{
			Student * stud = user->getStudent();

			if (stud->getFaculty().getAbbrev() == fac and 
				stud->getSpec().getAbbrev() == spec and 
				stoi(stud->getGroup().getName()) == stoi(group)) {
				req_users.push_back(user);
			}
		}
		sort(req_users.begin(), req_users.end(), UcompByFIO);

		return req_users;
	}

	void StudentRating(vector<Student *> students, vector<wstring> fac_spec_group)
	{
		if (fac_spec_group.size() != 3) { wcout << L"Неверный параметры"; return; }
		vector<Student *> req_stud;

		for (auto stud : students)
		{
			if (stud->getFaculty().getAbbrev() == fac_spec_group.at(0) and
				stud->getSpec().getAbbrev() == fac_spec_group.at(1) and
				stud->getGroup().getName() == fac_spec_group.at(2)) {	req_stud.push_back(stud); }
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

	void pprintAdditStipend(std::vector<Stipend*> stipends, std::wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		int max_size_name = 0, max_size_ratio = 0;

		for (int i = 0; i < stipends.size(); i++)
		{
			if (stipends.at(i)->getName().length() > max_size_name)
				max_size_name = stipends.at(i)->getName().length();

			if (to_string(stipends.at(i)->getRatio()).length() > max_size_ratio)
				max_size_ratio = to_string(stipends.at(i)->getRatio()).length();
		}

		int table_width = space_subjects + (
			(max_size_name > MIN_SPACE ? max_size_name + 1 : MIN_SPACE) +
			(max_size_ratio > MIN_SPACE ? max_size_ratio + 1 : MIN_SPACE));


		if (title.length())
		{
			int title_table_widht = (table_width - title.length()) / 2;
			wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
		}

		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";
		SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);

		wcout
			<< setw(5) << left << L"№"
			<< setw(max_size_name > MIN_SPACE ? max_size_name + 1 : MIN_SPACE) << left << L"Стипендия им."
			<< setw(max_size_ratio > MIN_SPACE ? max_size_ratio + 1 : MIN_SPACE) << left << L"Коэфф.";


		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << L"│" << endl;

		for (int j = 0; j < stipends.size(); j++) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│"
				<< setw(5) << j + 1
				<< setw(max_size_name > MIN_SPACE ? max_size_name + 1 : MIN_SPACE) << left << stipends[j]->getName()
				<< setw(max_size_ratio > MIN_SPACE ? max_size_ratio + 1 : MIN_SPACE) << left << stipends[j]->getRatio();
			wcout << left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	wstring ppWstring(wstring word)
	{
		if (word.length() > 0)
		{
			for (int i = 0; i < word.length(); i++) {
				word[i] = _towlower_l(word[i], _create_locale(LC_ALL, "Russian"));
			}
			//word[0] = _towupper_l(word[0], _create_locale(LC_ALL, "Russian"));
		}

		return word;
	}

	int choiceAdditStipend(vector<Stipend *> stipends)
	{
		return 0;
	}
}
