#include <iostream>
#include <Windows.h>

#include "LoginController.h"
#include "LoginController.cpp"
#include "Admin.h"
#include "User.h"
#include "Menu.h"


using namespace std;

int menu();

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	locale::global(std::locale(".utf-8"));

	int flag = 1;

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

	return 0;
}

