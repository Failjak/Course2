#include "UserController.h"
#include "Header.h"
#include "DataBase.h"


void UserController::main(User * user)
{
	DataBase<User> db;

	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			system("cls");
			PersonalInfo(user);
			break;
		}

		case 2:
		{
			system("cls");
			ShowMarks(user);
			break;
		}
		case 3:
		{
			system("cls");
			StipendManage(user);
			break;
		}
		case 4:
		{
			system("cls");
			Editing(user);
			break;
		}
		case 0:
			return;
		
		default:
			wcout << L"�������� �����." << endl;
			break;
		}
		system("cls");
	}
}

int UserController::menu()
{
	coutTitle(L"���� ��������");

	int choice;

	wcout << L"1) - �������� ������������ ����������." << endl;
	wcout << L"2) - �������� ������." << endl;
	wcout << L"3) - ���������." << endl;
	wcout << L"4) - ��������������." << endl;
	wcout << L"5) - ������� ���������" << endl;
	wcout << L"0) - �����." << endl;
	wcout << L" ��� �����: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

int UserController::personal_menu()
{
	coutTitle(L"������������ ����������");

	int choice;

	wcout << L"1) - ��������." << endl;
	wcout << L"2) - ��������������." << endl;
	wcout << L"0) - �����." << endl;
	wcout << L" ��� �����: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

void UserController::PersonalInfo(User *)
{
	while (true)
	{
		switch (personal_menu())
		{
		case 1:
		{

		}
		case 2:
		{

		}
		case 0:
			return;

		default:
			wcout << L"�������� �����." << endl;
			break;
		}
		system("cls");
	}
}

void UserController::ShowMarks(User *)
{
}

void UserController::StipendManage(User *)
{
}

void UserController::Editing(User *)
{
}
