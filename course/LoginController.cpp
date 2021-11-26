#include <conio.h>

#include "Header.h"
#include "LoginController.h"

template<class T>
wstring LoginController<T>::clear_input(wstring word, int mode)
{
	/*
		mode=1 input nothing
		mode=0 input entered char
	*/

	int ch = 0;
	while (true)
	{
		ch = _getch();
		if (ch == 13) { break; }
		if (ch == 32) { continue; }
		if (ch == 8)
		{
			if (word.length() > 0)
			{
				if (!mode) { wcout << (wchar_t)8 << ' ' << wchar_t(8); }
				word.erase(word.length() - 1, word.length());
			}
		}
		else
		{
			if (!mode) { wcout << (wchar_t)ch; }
			word += (wchar_t)ch;
		}
	}
	return word;
}

template <class T>
bool LoginController<T>::chekAuth(T * s)
{
	vector<T> lp;
	DataBase<T> db;
	int flag = 1;

	while (flag)
	{
		wstring login, password;

		wcout << L"Введите логин: ";
		login = clear_input(login, 0);
		wcout << endl;
		if (login == L"0") { return false; }
		wcout << L"Введите пароль: ";
		password = clear_input(password);
		wcout << endl;
		if (password == L"0") { return false; }

		s->setLogin(login);
		s->setPassword(password);

		if (db.exist(s))
		{
			return true;
		}

		wcout << L"\nНеверный логин или пароль.(0 - выйти в главное меню)" << endl;
	}

	return false;
}
