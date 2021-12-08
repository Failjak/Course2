#include "AdminController.h"
#include "Header.h"
#include "DataBase.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>

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
				break;
			}
			case 4:
			{
				system("cls");
				StipendManage(admin);
				break;
			}
			case 5: // Редактирование пользвателей
			{
				system("cls");
				EditManage(admin);
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

		bool flag = true;
		wstring choice;

		wcout << L"1) - Работа с пользователями." << endl;
		wcout << L"2) - Работа со студентами." << endl;
		wcout << L"3) - Выставить оценки." << endl;
		wcout << L"4) - Просмотр стпипендий." << endl;
		wcout << L"5) - Редактирование пользователей." << endl;
		wcout << L"0) - Назад." << endl;

		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"5") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	int user_menu()
	{
		coutTitle(L"Меню управления пользователями");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Просмотр пользователей." << endl;
		wcout << L"2) - Добавить пользователя" << endl;
		wcout << L"3) - Удалить пользователя." << endl;
		wcout << L"0) - Назад." << endl;
		wcout << L" Ваш выбор: ";
		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"3") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	int stud_menu()
	{
		coutTitle(L"Меню управления студентами");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Просмотр студентов." << endl;
		wcout << L"2) - Рейтинг студентов." << endl;
		wcout << L"3) - Добавить студента" << endl;
		wcout << L"4) - Удалить студена." << endl;
		wcout << L"0) - Назад." << endl;
		wcout << L" Ваш выбор: ";
		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"4") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	int marks_menu()
	{
		coutTitle(L"Меню добавления оценок");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Выбор студента." << endl;
		wcout << L"2) - Добавление по id студента." << endl;
		wcout << L"0) - Назад." << endl;
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

	int stipend_menu()
	{
		coutTitle(L"Меню просмотра стипендий");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Вычислить стипендию для студента(за последний семестр)." << endl;
		wcout << L"0) - Назад." << endl;
		wcout << L" Ваш выбор: ";
		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"1") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
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

	void pprinStudent(std::vector<Student*> students, std::wstring title)
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

			if (students.at(i)->getFaculty().length() > max_size_fac)
				max_size_fac = students.at(i)->getFaculty().size();

			if (students.at(i)->getSpec().length() > max_size_spec)
				max_size_spec = students.at(i)->getSpec().size();

			if (students.at(i)->getGroup().length() > max_size_group)
				max_size_group = students.at(i)->getGroup().size();

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
				<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << students[j]->getFaculty()
				<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << students[j]->getSpec()
				<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << students[j]->getGroup()
				<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << students[j]->getAvgMark()
				<< setw(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) << left << students[j]->getEdFormWstr()
				<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << students[j]->getEmail()
				<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << students[j]->getPhone()
				<< left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void pprinStipend(std::vector<Student*> students, std::wstring title)
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
				<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << std::fixed << std::setprecision(2) << students[j]->getStipendLastTerm()
				<< left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void StudentRating(Admin * s)
	{
		coutTitle(L"Рейтинг студентов");

		wstring fac, spec, group;
		DataBase db;
		//vector<Student *> students = db.getStudents();
		vector<Student *>students = s->getStudents();

		wcout << L"Выберете следующие поля: " << endl;

		fac = s->EnterFaculty();
		spec = s->EnterSpec(fac);
		group = s->EnterGroup(fac, spec);

		AbstractHandler::StudentRating(students, {fac, spec, group});

		system("pause");
		system("cls");
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

				int id;
				vector<User*> users = admin->getUsers();

				AdminController::pprintUser(users, L"Удаление пользователя");
				wcout << L"№ пользователя для удаление: ";
				wcin >> id;

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

				AdminController::pprinStudent(students, L"Студенты");

				system("pause");
				system("cls");

				break;
			}
			case 2:
			{
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
				int id;
				vector<Student*> students = admin->getStudents();

				AdminController::pprinStudent(students, L"Удаление студента");
				wcout << L"№ студентя для удаление: ";
				wcin >> id;

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

			int id;
			vector<Student*> students = admin->getStudents();

			AdminController::pprinStudent(students, L"Добавление оценок");
			wcout << L"№ студента: ";
			wcin >> id;

			try
			{
				if (admin->AddMarksToStudent(students.at(id - 1)) == 1)
				{
					wcout << L"Добавление оценок прошло успешно." << endl;
				}
				else {
					wcout << L"Ошибка добавление оценок." << endl;
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
		case 2: // Добавляем по id
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Добавление оценок");

			wcout << L"ID-студента: ";
			wcin >> student_id;

			try
			{
				int res = admin->AddMarksToStudent(student_id);
				if (res == 1)
				{
					wcout << L"Добавление оценок прошло успешно." << endl;
				}
				else if (!res) {
					wcout << L"Ошибка добавление оценок." << endl;
				}
				else if (res == -1) {}
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
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	void StipendManage(Admin * admin)
	{
		switch (stipend_menu())
		{
		case 1: // Расчет по id 
		{
			system("cls");

			wstring student_id;
			coutTitle(L"Раcчет стипендии(за текущий семестр)");

			wcout << L"ID-студента: ";
			CIN_FLUSH;
			wcin >> student_id;

			vector<Student * > students = admin->getStudents(student_id);
			if (!students.size()) { break; }

			pprinStipend(students);

			system("pause");
			system("cls");
			break;
		}
		case 0:
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

		system("pause");
		system("cls");
	}
}