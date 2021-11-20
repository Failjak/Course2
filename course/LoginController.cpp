#include "LoginController.h"
#include <conio.h>


template<class T>
wstring LoginController<T>::clear_input(wstring word)
{
	int ch = 0;
	while (true)
	{
		ch = _getch();
		if (ch == 13) { break; }
		if (ch == 8)
		{
			if (word.length())
			{
				cout << (char)8 << ' ' << char(8);
				word.erase(word.length() - 1);
			}
		}
		else
		{
			word += (char)ch;
		}
	}
	return word;
}

template <class T>
bool LoginController<T>::chekAuth(T s)
{
	vector<T> lp;
	int flag = 1;

	while (flag)
	{
		wstring login, password;

		wcout << L"Введите логин: ";
		wcin >> login;
		wcout << L"Введите пароль: ";
		password = clear_input(password);

		lp = ReadFromFile(s);

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
		}
		wcout << L"Неверный логин или пароль." << endl;
	}

	return false;
}

template <class T>
vector<T> LoginController<T>::ReadFromFile(T s)
{
	std::vector<T> res;
	wstring login, pass;

	wifstream in;

	if (is_same<T, Admin>::value)
	{
		in.open(admin_file);
	}
	else {
		in.open(user_file);
	}

	if (in.is_open())
	{
		while (in >> login >> pass)
		{
			s.setLogin(login);
			s.setPassword(pass);

			res.push_back(s);
		}

		in.close();
	}

	return res;
}