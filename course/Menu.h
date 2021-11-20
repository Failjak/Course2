#pragma once
#include <iostream>

#include "Header.h"

using namespace std;

int type_menu()
{
	int choice;

	wcout << L"1) Войти как администратор." << endl;
	wcout << L"2) Войти как студент." << endl;
	wcout << L"3) Выход." << endl;

	CIN_FLUSH;
	cin >> choice;

	return choice;
}