#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "sqlite/sqlite3.h"

using namespace std;


/*----------------Class DataBase--------------------*/
template <class T>
class DataBase {
private:
	const char* db_path = "migrate/test.db";

public:
	bool exist(T);
};

static int callback(void *pUser, int argc, char** argv, char** azColName)
{
	int *flag = (int*)pUser;
	*flag = 1;

	return 1;
}

template <class T>
inline
bool DataBase<T>::exist(T s)
{
	wstring login = s.getLogin();
	wstring pass = s.getPassword();

	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(db_path, &DB);

	string sql("select password from admin where login like @login;");
	if (exit) {
		wcerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return -1;
	}

	char *pError = NULL;
	int fHasResult = 0;
	int result = sqlite3_exec(DB, sql.c_str(), callback, &fHasResult, &pError);

	if (result != SQLITE_OK) {
		wcout << L"Error was: " << pError << endl;
		free(pError);
	}

	sqlite3_close(DB);

	if (fHasResult) {
		return true;
	}
	else {
		return false;
	}
}