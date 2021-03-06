#include "AdminController.h"
#include "Header.h"
#include <algorithm>

using namespace std;

namespace AdminController
{
	void main(Admin * admin)
	{
		int flag = 1;

		while (flag)
		{
			switch (menu())
			{
			case 1:
			{
				system("cls");
				UserManageController(admin);
				break;
			}

			case 2:
			{
				system("cls");
				StudentManageController(admin);
				break;
			}
			case 3:
			{
				system("cls");
				MarksManage(admin);

				system("pause");
				system("cls");
				break;
			}
			case 4:
			{
				system("cls");

				StipendManage(admin);

				system("pause");
				system("cls");
				break;
			}
			case 5:
			{
				system("cls");
				EditManage(admin);

				system("pause");
				system("cls");
				break;
			}
			case 0:
			{
				flag = 0;
				return;
			}
			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
			system("cls");
		}
	}

	int menu()
	{
		coutTitle(L"Меню Администратора");

		vector<wstring> cols = {
			L"Работа с пользователями." ,
			L"Работа со студентами." ,
			L"Оценки." ,
			L"Стипендии.",
			L"Редактирование пользователей." ,
			L"Назад."
		};

		return AbstractHandler::choice_column(cols);
	}

	int user_menu()
	{
		coutTitle(L"Меню управления пользователями");

		vector<wstring> cols = {
			L"Просмотр пользователей.",
			L"Добавить пользователя.",
			L"Удалить пользователя.",
			L"Назад."
		};

		return AbstractHandler::choice_column(cols);
	}

	int stud_menu()
	{
		coutTitle(L"Меню управления студентами");

		vector<wstring> cols = {
			L"Просмотр студентов.",
			L"Рейтинг студентов.",
			L"Добавить студента.",
			L"Удалить студена.",
			L"Фильтры|Поиск.",
			L"Назад."
		};

		return AbstractHandler::choice_column(cols);
	}

	int marks_menu()
	{
		coutTitle(L"Меню оценок");

		vector<wstring> cols = { 
			L"Добавить оценки выбранному студенту.",
			L"Добавление по id студента." ,
			L"Просмотреть все оценки студента." ,
			L"Редактировать оценки студента." ,
			L"Назад.",
		};

		return AbstractHandler::choice_column(cols);
	}

	int stipend_out_menu()
	{
		coutTitle(L"Меню просмотра стипендий");

		vector<wstring> cols = { 
			L"Вычислить стипендию для всех студентов (за последний семестр).",
			L"Вычислить стипендию для студента (за последний семестр)." ,
			//L"Посмотреть наличие дополнительных стипендий." ,
			L"Назад.",
		};

		return AbstractHandler::choice_column(cols);
	}

	int stipend_menu()
	{
		coutTitle(L"Меню управления стипендиями");

		vector<wstring> cols = { L"Cтипендии студентов.",
			L"Назначение дополнительных стипендии." ,
			L"Дополнительные стипендии.",
			L"Назад.",
		};

		return AbstractHandler::choice_column(cols);
	}

	int additional_stipend_menu()
	{
		coutTitle(L"Меню управления дополнительными стипендиями");

		vector<wstring> cols = { 
			L"Просмотр дополнительных стипендий.",
			L"Добавить стипендию." ,
			L"Удалить стипендию.",
			L"Назад."
		};

		return AbstractHandler::choice_column(cols);
	} 

	int stipend_assign_menu()
	{
		coutTitle(L"Меню назначения дополнительных стипендий");

		vector<wstring> cols = { 
			L"Назначить стипендию студенту по id.",
			L"Назначить стипендию выбранному студенту." ,
			L"Удалить назначенную стипендию.",
			L"Назад."
		};

		return AbstractHandler::choice_column(cols);
	}

	void pprintUser(vector<User*> array, wstring title)
	{

		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		int max_size_login = 0, max_size_pass = 0, max_size_id = 0;
		for (int i = 0; i < array.size(); i++)
		{
			if (array.at(i)->getLogin().length() > max_size_login)
				max_size_login = array.at(i)->getLogin().size();
			if (array.at(i)->getPassword().length() > max_size_pass)
				max_size_pass = array.at(i)->getPassword().size();
			if (array.at(i)->getStudentId().length() > max_size_id)
				max_size_id = array.at(i)->getStudentId().size();
		}

		int table_width = space_subjects + ((max_size_pass > MIN_SPACE) ? max_size_pass + 1 : MIN_SPACE) +
			(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) +
			(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE);


		if (title.length())
		{
			int title_table_widht = table_width - title.length();
			wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
		}

		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";
		SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);

		wcout
			<< setw(5) << left << L"№"
			<< setw(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) << left << L"Логин "
			<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << L"Пароль "
			<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << L"ID студента ";

		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << L"│" << endl;

		for (int j = 0; j < array.size(); j++) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│"
				<< setw(5) << j + 1
				<< setw(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) << left << array[j]->getLogin()
				<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << array[j]->getPassword()
				<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << array[j]->getStudentId()
				<< left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void pprintStudent(std::vector<Student*> students, std::wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		int max_size_FN = 0, max_size_fac = 0, max_size_spec = 0,
			max_size_group = 0, max_size_av_mark = 0, max_size_ed_form = 0,
			max_size_mail = 0, max_size_phone = 0;

		for (int i = 0; i < students.size(); i++)
		{
			if (students.at(i)->getFullName().length() > max_size_FN)
				max_size_FN = students.at(i)->getFullName().size();

			if (students.at(i)->getFaculty().getAbbrev().length() > max_size_fac)
				max_size_fac = students.at(i)->getFaculty().getAbbrev().size();

			if (students.at(i)->getSpec().getAbbrev().length() > max_size_spec)
				max_size_spec = students.at(i)->getSpec().getAbbrev().size();

			if (students.at(i)->getGroup().getName().length() > max_size_group)
				max_size_group = students.at(i)->getGroup().getName().size();

			if (to_string(students.at(i)->getAvgMark()).length() > max_size_av_mark)
				max_size_av_mark = to_string(students.at(i)->getAvgMark()).length();

			if (students.at(i)->getEdFormWstr().length() > max_size_ed_form)
				max_size_ed_form = students.at(i)->getEdFormWstr().size();

			if (students.at(i)->getEmail().length() > max_size_mail)
				max_size_mail = students.at(i)->getEmail().size();

			if (students.at(i)->getPhone().length() > max_size_phone)
				max_size_phone = students.at(i)->getPhone().size();
		}

		int table_width = space_subjects + (
			(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) +
			(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) +
			(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) +
			(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) +
			(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) +
			(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) +
			(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) +
			(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE));


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
			<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << L"ФИО"
			<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << L"Факультет"
			<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << L"Спецальность"
			<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << L"Группа"
			<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << L"Ср. балл"
			<< setw(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) << left << L"Форма обучения"
			<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << L"Почта"
			<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << L"Телефон";


		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << L"│" << endl;

		for (int j = 0; j < students.size(); j++) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│"
				<< setw(5) << j + 1
				<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << students[j]->getFullName()
				<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << students[j]->getFaculty().getAbbrev()
				<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << students[j]->getSpec().getAbbrev()
				<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << students[j]->getGroup().getName()
				<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << students[j]->getAvgMark()
				<< setw(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) << left << students[j]->getEdFormWstr()
				<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << students[j]->getEmail()
				<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << students[j]->getPhone()
				<< left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void pprintStipend(std::vector<Student*> students, std::wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		int max_size_FN = 0, max_size_id = 0, max_size_av_mark = 0, max_size_stipend = 0;

		for (int i = 0; i < students.size(); i++)
		{
			if (students.at(i)->getStudentId().length() > max_size_id)
				max_size_id = students.at(i)->getStudentId().size();

			if (students.at(i)->getFullName().length() > max_size_FN)
				max_size_FN = students.at(i)->getFullName().size();

			if (to_string(students.at(i)->getAvgMark()).length() > max_size_av_mark)
				max_size_av_mark = to_string(students.at(i)->getAvgMark()).length();

			if (to_string(students.at(i)->getStipendLastTerm()).length() > max_size_stipend)
				max_size_stipend = to_string(students.at(i)->getStipendLastTerm()).size();
		}

		int table_width = space_subjects + (
			(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) +
			(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) +
			(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) +
			(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE));


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
			<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << L"ID"
			<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << L"ФИО"
			<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << L"Ср. балл"
			<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << L"Стипендия";


		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << L"│" << endl;

		for (int j = 0; j < students.size(); j++) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│"
				<< setw(5) << j + 1
				<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << students[j]->getStudentId()
				<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << students[j]->getFullName()
				<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << std::fixed << std::setprecision(2) << students[j]->getAvgMark()
				<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << std::fixed;
			if (students[j]->getEdFormInt())
				wcout << std::setprecision(2) << students[j]->getStipendLastTerm();
			else
				wcout << students[j]->getEdFormWstr();
			wcout << left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void pprintMark(Student * s, wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		map<int, map<wstring, int>> all_marks = s->getMarks();
		vector<wstring> subjs;

		vector<int> max_sizes_subjs;
		wstring title_term = L"Семестр";

		max_sizes_subjs.push_back(title_term.length());

		for (auto it = all_marks.cbegin(); it != all_marks.cend(); ++it)
		{
			for (auto n_it = (*it).second.cbegin(); n_it != (*it).second.cend(); ++n_it)
			{
				max_sizes_subjs.push_back(DB_SUBJS.count((*n_it).first) ? DB_SUBJS.at((*n_it).first).length() : 0);
				subjs.push_back((*n_it).first);
			}
			break;
		}

		int max_size_FN = s->getFullName().length();
		int max_size_term = title_term.length();
		int table_width = space_subjects + (
			(max_size_term > MIN_SPACE ? MIN_SPACE : max_size_term + 1));
		for (int i = 0; i < max_sizes_subjs.size(); i++)
			table_width += max_sizes_subjs.at(i);

		if (title.length())
		{
			int title_table_widht = (table_width - title.length()) / 2;
			wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
		}

		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";

		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << wstring((table_width - s->getFullName().length()) / 2, L' ')
			<< left << s->getFullName()
			<< wstring((table_width - s->getFullName().length()) / 2, L' ')
			<< left << L"│" << endl;

		wcout << L"├";
		for (auto size : max_sizes_subjs)
			wcout << wstring(size > MIN_SPACE ? MIN_SPACE : size + 1, L'─') << left << L"┬";
		wcout << (wchar_t)8 << L"┤" << endl;

		wcout << left << L"│";
		SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);
		wcout << setw(max_sizes_subjs.at(0) + 1) << left << title_term;
		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << right << L"│";

		for (int i = 0; i < subjs.size(); i++) // перечисление предметов
		{
			SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);
			wcout << setw(max_sizes_subjs.at(i + 1) + 1) << left << DB_SUBJS.at(subjs.at(i));

			SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			wcout << right << L"│";
		}
		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

		wcout << endl << L"├";
		for (auto size : max_sizes_subjs)
			wcout << wstring(size > MIN_SPACE ? MIN_SPACE : size + 1, L'─') << left << L"┼";
		wcout << (wchar_t)8 << L"┤" << endl;

		for (auto it = all_marks.cbegin(); it != all_marks.cend(); ++it)
		{
			if (it != all_marks.cbegin())
			{
				wcout << endl << L"├";
				for (auto size : max_sizes_subjs)
					wcout << wstring(size > MIN_SPACE ? MIN_SPACE : size + 1, L'─') << left << L"┼";
				wcout << (wchar_t)8 << L"┤" << endl;
			}

			wcout << left << L"│" << setw(max_size_term + 1) << left << (*it).first << left << L"│";
			int i = 0;
			for (auto n_it = (*it).second.cbegin(); n_it != (*it).second.cend(); ++n_it, i++)
				wcout << setw(max_sizes_subjs.at(i + 1) + 1) << left << (*n_it).second << left << L"│";
		}

		wcout << endl << L"└";
		for (auto size : max_sizes_subjs)
			wcout << wstring(size > MIN_SPACE ? MIN_SPACE : size + 1, L'─') << left << L"┴";
		wcout << (wchar_t)8 << L"┘" << endl;
	}

	void StudentRating(Admin * s)
	{
		coutTitle(L"Рейтинг студентов");

		Faculty * fac;
		Speciality * spec;
		Group *group;

		DataBase db;
		vector<Student *>students = s->getStudents();

		wcout << L"Выберете следующие поля: " << endl;

		fac = s->EnterFaculty();
		if (fac->getId() < 0) { wcout << L"Отмена"; return; }
		spec = s->EnterSpec(*fac);
		if (spec->getAbbrev() == L"-1") { wcout << L"Отмена"; return; }
		group = s->EnterGroup(*fac, *spec);
		if (group->getName() == L"0") { wcout << L"Отмена"; return; }

		AbstractHandler::StudentRating(students, {fac->getAbbrev(), spec->getAbbrev(), group->getName()});
	}

	void UserManageController(Admin * admin)
	{
		int flag = 1;

		while (flag)
		{

			switch (user_menu())
			{
			case 1: // Просмотр пользоватлей
			{
				system("cls");

				vector<User*> users = admin->getUsers();

				AdminController::pprintUser(users, L"Пользователи");

				system("pause");
				system("cls");
				break;
			}

			case 2: // Добавить пользователей
			{
				if (admin->AddUser() == 1)
				{
					wcout << L"Добавление выполнено успешно." << endl;
				}
				else {
					wcout << L"Ошибка добавления." << endl;
				}
				system("pause");
				system("cls");
				break;
			}

			case 3: // Удалить пользователя
			{
				system("cls");

				vector<User*> users = admin->getUsers();

				AdminController::pprintUser(users, L"Удаление пользователя");
				wcout << L"№ пользователя для удаления: ";
				int id = AbstractHandler::choice_number(users.size());

				try {
					if (admin->DelUser(users.at(id - 1)) == 1)
					{
						wcout << L"Удаление выполнено успешно." << endl;
					}
					else {
						wcout << L"Ошибка удаления." << endl;
					}
				}
				catch (std::out_of_range)
				{
					wcout << L"Неверный выбор" << endl;
				}

				system("pause");
				system("cls");
				break;
			}
			case 0:
				flag = 0;
				break;
			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
		}

		return;
	}

	void StudentManageController(Admin * admin)
	{
		int flag = 1;

		while (flag)
		{

			switch (stud_menu())
			{
			case 1: // Просмотр студентов (фио, фак, специальность, группа, средняя оценка, стипендия(если бюджет), mail, phone)
			{
				system("cls");

				vector<Student*> students = admin->getStudents();

				sort(students.begin(), students.end(), AbstractHandler::ScompByFIO);
				AdminController::pprintStudent(students, L"Студенты");

				system("pause");
				system("cls");

				break;
			}
			case 2:
			{
				system("cls");

				StudentRating(admin);

				system("pause");
				system("cls");
				break;
			}
			case 3: // Добавление студента
			{
				try {
					if (admin->AddStudent() == 1)
					{
						wcout << L"Добавление выполнено успешно." << endl;
					}
					else {
						wcout << L"Ошибка добавления." << endl;
					}
				}
				catch (std::out_of_range)
				{
					wcout << L"Неверный выбор" << endl;
				}

				system("pause");
				system("cls");
				break;
			}
			case 4: // Удаление студента
			{
				vector<Student*> students = admin->getStudents();

				AdminController::pprintStudent(students, L"Удаление студента");
				wcout << L"№ студента для удаление: ";
				int id = AbstractHandler::choice_number(students.size());

				try
				{
					if (admin->DelStudent(students.at(id - 1)) == 1)
					{
						wcout << L"Удаление выполнено успешно." << endl;
					}
					else {
						wcout << L"Ошибка удаления." << endl;
					}
				}
				catch (std::out_of_range)
				{
					wcout << L"Неверный выбор" << endl;
				}

				system("pause");
				system("cls");
				break;
			}
			case 5:
			{
				system("cls");

				ManageData(admin);

				system("pause");
				system("cls");
				break;
			}
			case 0:
				flag = 0;
				break;

			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
		}
	}

	void MarksManage(Admin * admin)
	{
		switch (marks_menu())
		{
		case 1: // Выбираем студента сами
		{
			system("cls");
			coutTitle(L"Добавление оценок");
			vector<Student*> students = admin->getStudents();
			
			while (true)
			{
				AdminController::pprintStudent(students, L"Добавление оценок");
				wcout << L"№ студента(0 - Выход): ";

				int id = AbstractHandler::choice_column(students.size());
				if (!id) { break; }

				try
				{
					int res = admin->AddMarksToStudent(students.at(id - 1));
					if (res == 1)
					{
						wcout << L"Добавление оценок прошло успешно." << endl;
					}
					else if(res == -1) {
						wcout << L"Ошибка добавление оценок." << endl;
					}
					else if (res == 0) {
						wcout << L"Отмена добавления оценок." << endl;
						break;
					}
				}
				catch (std::out_of_range)
				{
					wcout << L"Неверный выбор" << endl;
				}
			}
			break;
		}
		case 2: // Добавляем по id
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Добавление оценок");

			wcout << L"ID-студента: ";
			wcin >> student_id;

			int res = admin->AddMarksToStudent(student_id);
			if (res == 1)
			{
				wcout << L"Добавление оценок прошло успешно." << endl;
			}
			else if (res == -1) {
				wcout << L"Ошибка добавление оценок." << endl;
			}
			else if (res == 0) {
				wcout << L"Отмена добавления оценок." << endl;
				break;
			}
			break;
		}

		case 3:
		{
			coutTitle(L"Просмотр оценок для студента");
			system("cls");
			
			wstring student_id;

			wcout << L"ID-студента: ";
			getline(wcin, student_id);

			Student* student = admin->getStudents(student_id).at(0);
			pprintMark(student);
			break;
		}

		case 4:
		{
			wstring student_id;

			coutTitle(L"Редактирование оценок для студента");
			system("cls");

			wcout << L"ID-студента: ";
			getline(wcin, student_id);

			Student* student = admin->getStudents(student_id).at(0);
			pprintMark(student);
			wcout << L"Семестр для редактирования: ";
			int choice_term = AbstractHandler::choice_number(student->getMarks().size());

			admin->EditMarks(student, choice_term);

			break;
		}

		case 0:
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	void StipendManage(Admin * admin)
	{
		while (true)
		{
			switch (stipend_menu())
			{
			case 1:
			{
				system("cls");

				StipendOutput(admin);
				break;
			}
			case 2:
			{
				system("cls");

				StipendAssign(admin);
				break;
			}
			case 3:
			{
				system("cls");

				AdditionalStipend(admin);
				break;
			}
			case 0:
				return;

			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
		}
	}

	void StipendAssign(Admin * admin)
	{
		switch (stipend_assign_menu())
		{
		case 1:
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Назначение стипендии");

			wcout << L"ID-студента: ";
			wcin >> student_id;

			int res = admin->AddStipendToStudent(student_id);
			if (res == 1)
			{
				wcout << L"Назначение стипендии прошло успешно." << endl;
			}
			else if (res == -1) {
				wcout << L"Ошибка назначения стипендии." << endl;
			}
			else if (res == 0) {
				wcout << L"Отмена назначения стипендии." << endl;
				break;
			}

			break;
		}
		case 2:
		{
			system("cls");

			int id, ch;
			wstring num;
			vector<Student*> students = admin->getStudents();

			while (true)
			{
				AdminController::pprintStudent(students, L"Назначение стипендий");
				wcout << L"№ студента(0 - Выход): ";

				int id = AbstractHandler::choice_column(students.size());
				if (!id) { break; }

				try
				{
					int res = admin->AddStipendToStudent(students.at(id - 1));
					if (res == 1)
					{
						wcout << L"Назначение стипендии прошло успешно." << endl;
					}
					else if (res == -1) {
						wcout << L"Ошибка назначения стипендии." << endl;
					}
					else if (res == 0) {
						wcout << L"Отмена назначения стипендии." << endl;
						break;
					}
				}
				catch (std::out_of_range)
				{
					wcout << L"Неверный выбор" << endl;
				}
			}

			system("pause");
			system("cls");
			break;
		}
		case 3: // удаление стипендии
		{
			system("cls");

			vector<Student*> students = admin->getStudents();

			AdminController::pprintStudent(students, L"Удаление доп. стипендии у студента");
			wcout << L"№ студента для удаления доп. стипендии: ";
			int id = AbstractHandler::choice_number(students.size());

			try
			{
				if (admin->delStipendToStudent(students.at(id - 1)) == 1)
				{
					wcout << L"Удаление выполнено успешно." << endl;
				}
				else {
					wcout << L"Ошибка удаления." << endl;
				}
			}
			catch (std::out_of_range)
			{
				wcout << L"Неверный выбор" << endl;
			}

			system("pause");
			system("cls");
			break;
		}
		case 0:
			system("cls");
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	void AdditionalStipend(Admin * admin)
	{
		DataBase db;

		switch (additional_stipend_menu())
		{
		case 1: // просмотр
		{
			system("cls");

			vector<Stipend *> stipends = db.getAdditStipends();
			AbstractHandler::pprintAdditStipend(stipends, L"Просмотр дополнительных стипендий");

			system("pause");
			system("cls");
			break;
		}
		case 2: // добавить
		{
			system("cls");

			admin->AddAdditionalStipend();

			system("pause");
			system("cls");
			break;
		}
		case 3: // удалить
		{
			system("cls");
	
			vector<Stipend *> stipends = db.getAdditStipends();
			AbstractHandler::pprintAdditStipend(stipends, L"Удаление дополнительных стипендий");

			wcout << L"№ записи для удаления: ";
			int id = AbstractHandler::choice_number(stipends.size());

			try
			{
				if (admin->DelStipend(stipends.at(id - 1)) == 1)
				{
					wcout << L"Удаление выполнено успешно." << endl;
				}
				else {
					wcout << L"Ошибка удаления." << endl;
				}
			}
			catch (std::out_of_range)
			{
				wcout << L"Неверный выбор" << endl;
			}

			system("pause");
			system("cls");
			break;
		}
		case 0:
			system("cls");
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	void StipendOutput(Admin * admin)
	{
		switch (stipend_out_menu())
		{
		case 1:
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Раcчет стипендии для всех студентов(за последний семестр)");
			vector<Student * > students = admin->getStudents();

			if (!students.size()) {
				wcout << L"Список студентов пуст." << endl;
				system("pause");
				system("cls");
				break;
			}
			pprintStipend(students);

			int choice = AbstractHandler::choice_column({ L"Сделать отчет.", L"Назад." });
			if (choice == 1) { MakeStipendInfo2Report(students); }
				
			system("pause");
			system("cls");
			break;
		}
		case 2: // Расчет по id 
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Раcчет стипендии(за последний семестр)");

			wcout << L"ID-студента: ";
			CIN_FLUSH;
			wcin >> student_id;

			vector<Student * > students = admin->getStudents(student_id);
			if (!students.size()) { 
				wcout << L"Студентов с таким id нет." << endl; 
				system("pause");
				system("cls");
				break; 
			}

			sort(students.begin(), students.end(), AbstractHandler::ScompByFIO);

			pprintStipend(students);

			int choice = AbstractHandler::choice_column({ L"Сделать отчет.", L"Назад." });
			if (choice == 1) { MakeStipendInfo2Report(students); }

			system("pause");
			system("cls");
			break;
		}
		case 0:
			system("cls");
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	void EditManage(Admin * admin)
	{
		int id;
		vector<User*> users = admin->getFullUser();

		AdminController::pprintUser(users, L"Редактирование пользователей");
		wcout << L"№ пользователя для редактирования: ";
		wcin >> id;

		try
		{
			int res = admin->EditUser(users.at(id - 1));

			if (res == 1)
			{
				wcout << L"Редактирование выполнено успешно." << endl;
			}
			else if (res == -1) {
				wcout << L"Отмена редактирования." << endl;
			}
			else {
				wcout << L"Ошибка редактирования." << endl;
			}
		}
		catch (std::out_of_range)
		{
			wcout << L"Неверный выбор" << endl;
		}

		return;
	}
	
	void ManageData(Admin * admin)
	{
		DataBase db;

		system("cls");
		coutTitle(L"Сортировка пользователей");

		vector<User*> users = admin->getFullUser();

		wcout << L"Фильтрация или Поиск? (1 & 2):" << endl;
		int choice = AbstractHandler::choice_column({L"Фильтры", L"Поиск"});

		if (choice == 1)
		{
			FilterManage(admin, users);
		}
		else if (choice == 2)
		{
			SearchManage(admin, users);
		}

		return;
	}

	void FilterManage(Admin * admin, vector<User*> users)
	{
		vector<User*> req_users;

		coutTitle(L"Применение фильтров к данным");
		wcout << L"Вывести выборку по:" << endl;

		vector<wstring> columns = {
			L"Факульету",
			L"Специальности",
			L"Группе",
			L"Форме обучения"
		};
		int choice = AbstractHandler::choice_column(columns);

		if (choice == 1)
		{
			Faculty * fac = admin->EnterFaculty();

			 req_users = AbstractHandler::filterByFSG(users, fac->getAbbrev());
		}
		else if (choice == 2)
		{
			Faculty * fac = admin->EnterFaculty();
			Speciality * spec = admin->EnterSpec(*fac);

			req_users = AbstractHandler::filterByFSG(users, fac->getAbbrev(), spec->getAbbrev());
		}
		else if (choice == 3)
		{
			Faculty * fac = admin->EnterFaculty();
			Speciality * spec = admin->EnterSpec(*fac);
			Group * group = admin->EnterGroup(*fac, *spec);

			req_users = AbstractHandler::filterByFSG(users, fac->getAbbrev(), spec->getAbbrev(), group->getName());
		}
		else if (choice == 4)
		{
			int ed_form = admin->EnterEdForm();

			req_users = AbstractHandler::filterByEdForm(users, ed_form);
		}

		if (!req_users.size()) { wcout << L"Ничего не найдено" << endl; }

		vector<Student *> students;
		for (auto us : req_users)
			students.push_back(new Student(*us->getStudent()));

		pprintStudent(students);

		return;
	}

	void SearchManage(Admin * admin, vector<User*> users)
	{
		vector<User*> req_users;

		coutTitle(L"Поиск в данных");
		wcout << L"Поиск по: " << endl;

		vector<wstring> columns = {
			L"Фамилии",
			L"Имени",
			L"Логину",
			L"Эл. почте",
			L"Телефону"
		};
		int choice = AbstractHandler::choice_column(columns);

		wstring srch_value;

		if (choice == 1)
		{
			wcout << L"Искомая Фамилия: ";
			wcin >> srch_value;

			req_users = AbstractHandler::searchSurname(users, srch_value);
		}
		else if (choice == 2)
		{
			wcout << L"Искомое Имя: ";
			wcin >> srch_value;

			req_users = AbstractHandler::searchName(users, srch_value);
		}
		else if (choice == 3)
		{
			wcout << L"Искомый Логин: ";
			wcin >> srch_value;

			req_users = AbstractHandler::searchLogin(users, srch_value);
		}
		else if (choice == 4)
		{
			wcout << L"Искомую почту: ";
			wcin >> srch_value;

			req_users = AbstractHandler::searchMail(users, srch_value);
		}
		else if (choice == 5)
		{
			wcout << L"Искомый номер телефонв: ";
			wcin >> srch_value;

			req_users = AbstractHandler::searchPhone(users, srch_value);
		}

		if (!req_users.size()) { wcout << L"Ничего не найдено" << endl; }

		vector<Student *> students;
		for (auto us : req_users)
			students.push_back(new Student(*us->getStudent()));

		pprintStudent(students);

		return;
	}

	int MakeReport(vector<wstring> cols, vector<vector<wstring>> values, wstring file_name)
	{
		wofstream myfile;
		myfile.open(L"reports\\" + file_name + L".csv", ios::out);
		locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
		myfile.imbue(loc);

		for (auto col : cols)
		{
			myfile << col;
			myfile << L",";
		}
		myfile << L"\n";
		for (auto vals : values)
		{
			for (auto val : vals)
			{
				myfile << val;
				myfile << L",";
			}
			myfile << L"\n";
		}

		myfile.close();
		return 0;
	}

	void MakeStipendInfo2Report(vector<Student * > students)
	{
		vector<wstring> cols = {
			L"№",
			L"ID",
			L"ФИО",
			L"Средний балл",
			L"Стипендия"
		};

		vector<vector<wstring>> values;

		int i = 0;
		for (auto stud : students)
		{
			vector<wstring> tmp{
				to_wstring(++i),
				stud->getStudentId(),
				stud->getFullName(),
				to_wstring(stud->getAvgMark()),
			};
			if (stud->getEdFormInt())
				tmp.push_back(to_wstring(stud->getStipendLastTerm()));
			else
				tmp.push_back(stud->getEdFormWstr());

			values.push_back(tmp);
		}
		
		if (students.size() == 1)
			MakeReport(cols, values, students.at(0)->getFullName());
		else
			MakeReport(cols, values, L"report_all_students");
	}
}