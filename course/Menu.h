#pragma once
#include <iostream>
#include "Header.h"

using namespace std;

int type_menu()
{
	coutTitle(L"Главное Меню");

	bool flag = true;
	wstring choice;

	wcout << L"1) - Войти как администратор." << endl;
	wcout << L"2) - Войти как студент." << endl;
	wcout << L"0) - Выход." << endl;

	while (flag)
	{
		rewind(stdin);
		getline(wcin, choice);
		if (choice >= L"0" && choice <= L"2") flag = false;
		else {
			wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
			choice = L"";
		}
	}

	return stoi(choice);
}