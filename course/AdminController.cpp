#include "AdminController.h"
#include "Header.h"
#include "DataBase.h"
#include <iostream>
#include <iomanip>

using namespace std;

void AdminController::main()
{
	int flag = 1;

	while (flag)
	{
		switch (menu())
		{
		case 1:
		{	
			UserManageController();
			break;
		}

		case 2:
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
		system("cls");
	}
}

int AdminController::menu()
{
	int choice;

	wcout << L"1) - Работа с пользователями." << endl;
	wcout << L"2) - Работа со студентами." << endl;
	wcout << L"0) - Выход." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	cin >> choice;
	return choice;
}

int AdminController::user_menu()
{
	int choice;

	wcout << L"1) - Просмотр пользователей." << endl;
	wcout << L"1) - Добавить пользователя" << endl;
	wcout << L"3) - Удалить пользователя." << endl;
	wcout << L"0) - Выход." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	cin >> choice;
	return choice;
}

void AdminController::pprint(vector<vector<wstring>> array, wstring title)
{
	int space_subjects = 4;

	int max_size_login = 0, max_size_pass = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if (array.at(i).at(0).length() > max_size_login)
			max_size_login = array.at(i).at(0).size();
		if (array.at(i).at(1).length() > max_size_pass)
			max_size_pass = array.at(i).at(1).size();
	}

	int table_width = space_subjects + ((max_size_pass > 18) ? max_size_pass + 1 : 18) + (max_size_login > 18 ? max_size_login + 1 : 18);

	wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
	wcout << L"│";
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);

	wcout << L"Код предмета " << setw(max_size_login > 18 ? max_size_login + 1 : 18) << left << L"Название предмета "
		<< setw(max_size_pass > 18 ? max_size_pass + 1 : 18) << L"ФИО Преподавателя ";

	SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	wcout << L"│" << endl;
	for (register int j = 0; j < array.size(); j++) {
		wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
		wcout << L"│" << setw(13) << left << setw(max_size_login > 18 ? max_size_login + 1 : 18) << left << array[j].at(0)
			<< setw(max_size_pass > 18 ? max_size_pass + 1 : 18) << array[j].at(1);
			//<< setw(6) << array[j].hours
			//<< setw(7) << array[j].number_of_semester << L"│" << endl;
	}
	wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
}

void AdminController::UserManageController()
{
	int flag = 1;

	while (flag)
	{
		DataBase<User> db;
		switch (user_menu())
		{
		case 1: // Просмотр пользоватлей
		{
			system("cls");

			vector<vector<wstring>> users = db.getObj2V();

			AdminController::pprint(users, L"");

			system("pause");
			system("cls");
			break;
		}

		case 2: // Добавить пользователей
			break;

		case 3: // Удалить пользователя
			break;
		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}
}
