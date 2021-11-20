#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include "sqlite/sqlite3.h"


#include "LoginController.h"
#include "LoginController.cpp"
#include "Admin.h"
#include "User.h"
#include "Menu.h"
#include "DataBase.h"


using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	locale::global(std::locale(".utf-8"));

	int flag = 0;

	while (flag)
	{
		switch (type_menu())
		{
		case 1:
		{
			LoginController<Admin> lContr;
			Admin admin;
			system("cls");
			if (lContr.chekAuth(admin))
			{
				system("cls");
				wcout << L"Вход выполнен успешно." << endl;
				//AdminController(admin);
			}
			break;
		}
		case 2:
		{
			LoginController<User> lContr;
			User user;
			system("cls");
			if (lContr.chekAuth(user))
			{
				system("cls");
				wcout << L"Вход выполнен успешно." << endl;
				//UserController(user);
			}
			break;
		}

		case 3:

			return 0;
			break;

		default:
			wcout << L"Неверный выбор." << endl;
			break;
		}
	}

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);

	return 0;
}

