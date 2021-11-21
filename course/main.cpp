#include <iostream>
#include <Windows.h>

#include "LoginController.h"
#include "LoginController.cpp"
#include "AdminController.h"
#include "Admin.h"
#include "User.h"
#include "Menu.h"


using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	locale::global(std::locale(".utf-8"));

	system("chcp 65001");
	system("cls");

	int flag = 1;

	while (flag)
	{
		system("cls");
		//switch (type_menu())
		switch (1)
		{
		case 1:
		{
			Admin admin;
			/*LoginController<Admin> lContr;

			system("cls");
			if (lContr.chekAuth(&admin))
			{
				system("cls");
				wcout << L"Вход выполнен успешно.\n" << endl;
				AdminController::main();

				system("pause");
			}*/
			AdminController::main(&admin);
			break;
		}
		case 2:
		{
			LoginController<User> lContr;

			User user;
			system("cls");
			if (lContr.chekAuth(&user))
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

