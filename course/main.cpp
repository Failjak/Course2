#include <iostream>
#include <Windows.h>

#include "LoginController.h"
#include "LoginController.cpp"
#include "Admin.h"
#include "User.h"

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
		switch (menu())
		{
		case 1:
		{
			LoginController<Admin> lContr;
			Admin admin;
			system("cls");
			if (lContr.chekAuth(admin))
			{
				system("cls");
				wcout << L"���� �������� �������." << endl;
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
				wcout << L"���� �������� �������." << endl;
			}
			break;
		}

		default:
			wcout << L"�������� �����." << endl;
			break;
		}
	}

	return 0;
}

int menu()
{
	int choice;
	int flag = 1;

	wcout << L"1) ����� ��� �������������." << endl;
	wcout << L"2) ����� ��� �������." << endl;
	wcout << L"3) �����." << endl;
	cin >> choice;

	return choice;
}