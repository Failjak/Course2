#pragma once
#include <iostream>

#include "Header.h"

using namespace std;

int type_menu()
{
	int choice;

	wcout << L"1) ����� ��� �������������." << endl;
	wcout << L"2) ����� ��� �������." << endl;
	wcout << L"3) �����." << endl;

	CIN_FLUSH;
	cin >> choice;

	return choice;
}