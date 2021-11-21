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
			if (word.length())
			{
				wcout << (wchar_t)8 << ' ' << wchar_t(8);
				word.erase(word.length() - 1, 1);
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
		if (login == L"0") { return false; }
		wcout << endl;
		wcout << L"Введите пароль: ";
		password = clear_input(password);
		if (password == L"0") { return false; }
		wcout << endl;

		s->setLogin(login);
		s->setPassword(password);

		if (db.exist(&s))
		{
			

			return true;
		}
		
		/*lp = ReadFromFile(s);
		auto iter = lp.begin();
		while (iter != lp.end())
		{
			if (iter->getLogin() == login && iter->getPassword() == password)
			{
				s.setLogin(login);
				s.setPassword(password);
				return true;
			}

			++iter;
		}*/
		wcout << L"\nНеверный логин или пароль.(0 - выйти в главное меню)" << endl;
	}

	return false;
}

//template <class T>
//vector<T> LoginController<T>::ReadFromFile(T s)
//{
//	std::vector<T> res;
//	wstring login, pass;
//
//	wifstream in;
//
//	if (is_same<T, Admin>::value)
//	{
//		in.open(admin_file);
//	}
//	else {
//		in.open(user_file);
//	}
//
//	if (in.is_open())
//	{
//		while (in >> login >> pass)
//		{
//			s.setLogin(login);
//			s.setPassword(pass);
//
//			res.push_back(s);
//		}
//
//		in.close();
//	}
//
//	return res;
//}