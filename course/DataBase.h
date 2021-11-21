#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <cstdlib> // char to wchar_t
#include "sqlite/sqlite3.h"

using namespace std;

class Admin;
class User;

/*----------------Class DataBase--------------------*/
template <class T>
class DataBase {
private:
	const char* db_path = "migrate/test.db";

public:
	int exist(T);
};

inline const std::wstring S2WS(const std::string &s)
{
	wstring ws;
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return ws;
}

inline std::string WS2S(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

template <class T>
inline
int DataBase<T>::exist(T s)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	string l = WS2S(s.getLogin());
	string pass = WS2S(s.getPassword());

	int res = 0;
	string table;
	//std::vector< std::vector < std::string > > result;

	if (is_same<T, Admin>::value)
	{
		table = "admin";
	}
	else if (is_same<T, User>::value) {
		table = "user";
	}

	if (sqlite3_open(db_path, &db) == SQLITE_OK)
	{
		string sql("select count(*) from " + table + " where login like '" + l + "' and password like '" + pass + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		res = sqlite3_column_int(stmt, 0);

		/*int i = 0;
		while (sqlite3_column_text(stmt, 0))
		{
			result.push_back(std::vector< std::string >());

			for (int j = 0; j < 2; j++)
			{
				result[i].push_back(string((char *)sqlite3_column_text(stmt, j)));
			}
			sqlite3_step(stmt);
			i++;
		}*/

	}
	else
	{
		cout << "Failed to open db\n";
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return res;

	/*for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[i].size(); j++)
		{
			wcout << S2WS(result[i][j]) << "''";
		}

		wcout << endl;
	}*/
}