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
			wcout << L"Неверный выбор." << endl;
			break;
		}
		system("cls");
	}
}

int UserController::menu()
{
	coutTitle(L"Меню Студента");

	int choice;

	wcout << L"1) - Просмотр персональной информации." << endl;
	wcout << L"2) - Просмотр оценок." << endl;
	wcout << L"3) - Стипендия." << endl;
	wcout << L"4) - Редактирование." << endl;
	wcout << L"5) - Рейтинг студентов" << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
	CIN_FLUSH;

	wcin >> choice;
	return choice;
}

int UserController::personal_menu()
{
	coutTitle(L"Персональная информация");

	int choice;

	wcout << L"1) - Просмотр." << endl;
	wcout << L"2) - Редактирование." << endl;
	wcout << L"0) - Назад." << endl;
	wcout << L" Ваш выбор: ";
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
			wcout << L"Неверный выбор." << endl;
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
