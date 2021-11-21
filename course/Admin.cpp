#include "Admin.h"
#include "Header.h"

vector<vector<wstring>> Admin::getUsers2V()
{
	DataBase<User> db;

	return db.getObj2V();
}

bool Admin::AddUser()
{
	/*
		return: 1 - no exeption;
				0 - faild insert.
	*/

	DataBase<User> db;
	wstring login, password;

	coutTitle(L"Добавление пользователя");

	wcout << L"Введите логин: ";
	wcin >> login;
	wcout << L"Введите пароль: ";
	wcin >> password;

	User user(login, password);

	if (db.exist(&user))
	{
		wcout << L"Такой пользователь уже существует." << endl;
		return -1;
	}

	if (db.AddNote(&user))
	{
		return true;
	}

	return false;
}
