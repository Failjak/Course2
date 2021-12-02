#pragma once
#include <iostream>

#include "Header.h"

using namespace std;

int type_menu()
{
	coutTitle(L"Главное Меню");

	int choice;

	wcout << L"1) Войти как администратор." << endl;
	wcout << L"2) Войти как студент." << endl;
	wcout << L"3) Выход." << endl;
	CIN_FLUSH;
	wcin >> choice;

	return choice;
}