#include "AdminController.h"
#include "Header.h"
#include "DataBase.h"
#include <iostream>
#include <iomanip>

using namespace std;

void AdminController::main(Admin * admin)
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

int AdminController::menu()
{
	coutTitle(L"Меню Администратора");

	int choice;

	wcout << L"1) - Работа с пользователями." << endl;
	wcout << L"2) - Работа со студентами." << endl;
	wcout << L"3) - Выставить оценки." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

int AdminController::user_menu()
{
	coutTitle(L"Меню управления пользователями");

	int choice;

	wcout << L"1) - Просмотр пользователей." << endl;
	wcout << L"2) - Добавить пользователя" << endl;
	wcout << L"3) - Удалить пользователя." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

int AdminController::stud_menu()
{
	coutTitle(L"Меню управления студентами");

	int choice;

	wcout << L"1) - Просмотр студентов." << endl;
	wcout << L"2) - Рейтинг студентов." << endl;
	wcout << L"3) - Добавить студента" << endl;
	wcout << L"4) - Удалить студена." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

int AdminController::marks_menu()
{
	coutTitle(L"Меню добавления оценок");

	int choice;

	wcout << L"1) - Выбор студента." << endl;
	wcout << L"2) - Добавление по id студента." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

void AdminController::pprintUser(vector<User*> array, wstring title)
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

void AdminController::pprinStudent(std::vector<Student*> students, std::wstring title)
{
	// (фио, фак, специальность, группа, средняя оценка, стипендия(если бюджет), mail, phone)
	int space_subjects = 5;
	int MIN_SPACE = 14;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	int max_size_FN = 0, max_size_fac = 0, max_size_spec = 0, 
		max_size_group = 0, max_size_av_mark = 0, max_size_stipend = 0, 
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

		if (to_string(students.at(i)->getAvgMark()).length() > max_size_av_mark) // ERROR
			max_size_av_mark = to_string(students.at(i)->getAvgMark()).length();
		//if (array.at(i)->getSpec().length() > max_size_stipend) // TO DO Сделать стипендию
			//max_size_stipend = array.at(i)->getSpec().size();

		if (students.at(i)->getGroup().length() > max_size_mail)
			max_size_mail = students.at(i)->getGroup().size();

		if (students.at(i)->getPhone().length() > max_size_phone)
			max_size_phone = students.at(i)->getPhone().size();
	}

	int table_width = space_subjects + (
		(max_size_FN > MIN_SPACE) ? max_size_FN + 1 : MIN_SPACE) +
		(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) +
		(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) +
		(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) +
		(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) +
		//(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) +
		(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) +
		(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE);


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
		<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << L"ФИО"
		<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << L"Факультет"
		<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << L"Спецальность"
		<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << L"Группа"
		<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << L"Ср. балл за все время"
		//<< setw(max_size_stipend > MIN_SPACE ? max_size_stipend + 1 : MIN_SPACE) << left << L"Стипендия"
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
			//<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << students[j]->get()
			<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << students[j]->getEmail()
			<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << students[j]->getPhone()
			<< left << L"│" << endl;
	}
	wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
}

void AdminController::UserManageController(Admin * admin)
{
	int flag = 1;

	while (flag)
	{
		
		switch (user_menu())
		{
		case 1: // Просмотр пользоватлей
		{
			system("cls");

			vector<User*> users = admin->getUsers2V();

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
			vector<User*> users = admin->getUsers2V();

			AdminController::pprintUser(users, L"Удаление пользователя");
			wcout << L"№ пользователя для удаление: ";
			wcin >> id;

			if (admin->DelUser(users.at(id-1)) == 1)
			{
				wcout << L"Удаление выполнено успешно." << endl;
			}
			else {
				wcout << L"Ошибка удаления." << endl;
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

void AdminController::StudentManageController(Admin * admin)
{
	int flag = 1;

	while (flag)
	{

		switch (stud_menu())
		{
		case 1: // Просмотр студентов (фио, фак, специальность, группа, средняя оценка, стипендия(если бюджет), mail, phone)
		{
			system("cls");

			vector<Student*> students = admin->getStudents2V();

			AdminController::pprinStudent(students, L"Студенты");

			system("pause");
			system("cls");

			break;
		}
		case 3: // Добавление студента
		{
			if (admin->AddStudent() == 1)
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
		case 4: // Удаление студента
		{
			int id;
			vector<Student*> students = admin->getStudents2V();

			AdminController::pprinStudent(students, L"Удаление студента");
			wcout << L"№ студентя для удаление: ";
			wcin >> id;

			if (admin->DelStudent(students.at(id - 1)) == 1)
			{
				wcout << L"Удаление выполнено успешно." << endl;
			}
			else {
				wcout << L"Ошибка удаления." << endl;
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

void AdminController::MarksManage(Admin * admin)
{
	/*
		Для начала выведем всех студентов и спросим для какого .
		Или же можно сделать меню:	1) Введи ид 
									2) Выберете пользователя сами
	*/

	switch (marks_menu())
	{
	case 1: // Выираем студента сами
	{
		system("cls");

		int id;
		vector<Student*> students = admin->getStudents2V();

		AdminController::pprinStudent(students, L"Добавление оценок");
		wcout << L"№ студента: ";
		wcin >> id;

		if (admin->AddMarksToStudent(students.at(id - 1)) == 1)
		{
			wcout << L"Добавление оценок прошло успешно." << endl;
		}
		else {
			wcout << L"Ошибка добавление оценок." << endl;
		}

		system("pause");
		system("cls");
		break;
	}
	case 2: // Добавляем по id // TODO Сделать валидацию на существование id
	{
		system("cls");

		wstring student_id;
		coutTitle(L"Добавление оценок");

		wcout << L"ID-студента: ";
		CIN_FLUSH;
		wcin >> student_id;

		if (admin->AddMarksToStudent(student_id) == 1)
		{
			wcout << L"Добавление оценок прошло успешно." << endl;
		}
		else {
			wcout << L"Ошибка добавление оценок." << endl;
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
