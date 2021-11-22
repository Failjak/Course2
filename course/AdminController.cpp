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
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	cin >> choice;
	return choice;
}

int AdminController::user_menu()
{
	coutTitle(L"Меню управления пользователями");

	int choice;

	wcout << L"1) - Просмотр пользователей." << endl;
	wcout << L"1) - Добавить пользователя" << endl;
	wcout << L"3) - Удалить пользователя." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	cin >> choice;
	return choice;
}

void AdminController::pprint(vector<User*> array, wstring title)
{

	int space_subjects = 5;
	int MIN_SPACE = 14;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	int max_size_login = 0, max_size_pass = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if (array.at(i)->getLogin().length() > max_size_login)
			max_size_login = array.at(i)->getLogin().size();
		if (array.at(i)->getPassword().length() > max_size_pass)
			max_size_pass = array.at(i)->getPassword().size();
	}

	int table_width = space_subjects + ((max_size_pass > MIN_SPACE) ? max_size_pass + 1 : MIN_SPACE) + 
		(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE);


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
		<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << L"Пароль ";

	SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	wcout << L"│" << endl;

	for (int j = 0; j < array.size(); j++) {
		wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
		wcout << L"│" 
			<< setw(5) << j + 1
			<< setw(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) << left << array[j]->getLogin()
			<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << array[j]->getPassword()
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

			AdminController::pprint(users, L"Пользователи");

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

			AdminController::pprint(users, L"Удаление пользователя");
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
}
