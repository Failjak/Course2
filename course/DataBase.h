#pragma once
#include "Header.h"
#include "sqlite/sqlite3.h"

using namespace std;

class Admin;
class Student;
class User;

/*----------------Class DataBase--------------------*/
template <class T>
class DataBase {
private: 
	string admin_table = "admin";
	string user_table = "users";
	string stud_table = "students";
	string mark_table = "marks";
	string group_table = "groups";

public:
	int exist(T * s);
	int existStudent(wstring student_id);
	vector<T*> getObj2V();
	
	/*-----Admin------*/
	int AddNoteUser(T *s);
	/*-----Admin------*/

	int DelNoteByStydentId(wstring id);


	/*-----Student------*/
	int AddNoteStudent(Student *s);
	int AddMarks2Student(vector<int> marks, Student *s);
	vector<Student*> getStudents2V();
	map<wstring, vector<wstring>> getGroup2V();
	vector<pair<int, vector<int>>> getMarks2VById(wstring student_id);
	Student * getStudentById(wstring id);
	/*-----Student------*/

	vector<wstring> getColNames(wstring table);

};
/*----------------End Class DataBase----------------*/

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

inline vector<vector<wstring>> VVS2VVWS(const vector<vector<string>> vvs)
{
	vector<vector<wstring>> vvws;
	wstring ws;

	for (int i = 0; i < vvs.size(); i++)
	{
		vvws.push_back(vector<wstring>());
		for (int j = 0; j < vvs[i].size(); j++)
		{
			std::wstring wsTmp(vvs[i][j].begin(), vvs[i][j].end());
			ws = wsTmp;
			vvws[i].push_back(ws);
		}
	}
	return vvws;
}

template <class T>
inline
int DataBase<T>::existStudent(wstring student_id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;


	int res = 0;
	string table;


	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select count(*) from " + stud_table + " where student_id like '" + WS2S(student_id) + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		res = sqlite3_column_int(stmt, 0);
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return res;
}

template <class T>
inline
int DataBase<T>::exist(T * s)
{
	/*
		Func get object and select from DB,
		if this obj exist the return 1.
		
		s = Admin or User type.
		return: 1 - good auth;
				0 - faild auth;
				-1 - faild opening db.
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;
	string l, pass;

	l = WS2S(s->getLogin());
	pass = WS2S(s->getPassword());

	int res = 0;
	string table;

	if (is_same<T, Admin>::value)
	{
		table = "admin";
	}
	else if (is_same<T, User>::value) {
		table = "user";
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select count(*) from " + table + " where login like '" + l + "' and password like '" + pass + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		res = sqlite3_column_int(stmt, 0);
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return res;
}

template<class T>
inline vector<T*> DataBase<T>::getObj2V()
{
	/*
		Func select from DB all T-type objects,
		if this obj exist the return 1.

		return: ...
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	vector<T*> result;

	if (is_same<T, Admin>::value)
	{
		table = "admin";
	}
	else if (is_same<T, User>::value) {
		table = "users";
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select * from " + table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{

			T *s = new T;
			s->setLogin(S2WS(string((char *)sqlite3_column_text(stmt, 0))));
			s->setPassword(S2WS(string((char *)sqlite3_column_text(stmt, 1))));

			if (sqlite3_column_text(stmt, 2)){ 
				s->setStudentId(S2WS(string((char *)sqlite3_column_text(stmt, 2))));
			}

			result.push_back(s);
			sqlite3_step(stmt);
		}

	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

template<class T>
inline int DataBase<T>::AddNoteUser(T * s)
{
	/*
		Func add inf about User to db.

		return: 1 - good auth;
				0 - faild auth;
				-1 - faild opening db.
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	/*if (is_same<T, Admin>::value)
	{
		table = "admin";
	}
	else if (is_same<T, User>::value) {
		table = "user";
	}*/

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("pragma foreign_keys=on;"
			"insert into "+ user_table + "(login, password, student_id) values ('" + WS2S(s->getLogin()) +
			"', '" + WS2S(s->getPassword()) + "', '" + WS2S(s->getStudentId()) + "');");

		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			//wcout << S2WS(err) << endl;
			return -1;
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_close(db);

	return 1;
}

template<class T>
inline
int DataBase<T>::DelNoteByStydentId(wstring id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	string table;

	if (is_same<T, User>::value)
	{
		table = user_table;
	}
	else if (is_same<T, Student>::value)
	{
		table = stud_table;
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("delete from " + table + " where student_id = '" + WS2S(id) + "';");

		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			wcout << S2WS(err) << endl;
			return -1;
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_close(db);
	return 1;
}

template<class T>
inline int DataBase<T>::AddNoteStudent(Student * s)
{
	/*
		Func add inf about Student to db.

		return: 1 - good auth;
				0 - faild auth;
				-1 - faild opening db.
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;


	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		wstring info = L"'" +  s->getStudentId() + L"'," + L"'" + s->getName() + L"'," + L"'" + s->getSurname() + L"'," + L"'" + s->getPatronomic() +
			L"'," + L"'" + s->getEdForm() + L"'," + L"'" + s->getEmail() + L"'," + L"'" + s->getPhone() + L"'";

		string sql("pragma foreign_keys=on;"
			"insert into " + stud_table + " values (" +  WS2S(info) + ");");

		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			wcout << S2WS(err) << endl;
			return 0;
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_close(db);

	return 1;
}

template<class T>
inline int DataBase<T>::AddMarks2Student(vector<int> marks, Student * s)
{
	/*
		Func add inf about Student to db.

		return: 1 - good auth;
				0 - faild auth;
				-1 - faild opening db.
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;


	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		/*wstring info = L"'" + s->getStudentId() + L"'," + L"'" + s->getName() + L"'," + L"'" + s->getSurname() + L"'," + L"'" + s->getPatronomic() +
			L"'," + L"'" + s->getEdForm() + L"'," + L"'" + s->getEmail() + L"'," + L"'" + s->getPhone() + L"'";

		string sql("pragma foreign_keys=on;"
			"insert into " + stud_table + " values (" + WS2S(info) + ");");*/

		/*int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			wcout << S2WS(err) << endl;
			return 0;
		}*/
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_close(db);

	return 1;
}

template<class T>
inline vector<Student*> DataBase<T>::getStudents2V()
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<T*> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select student_id, first_name, last_name, patronymic, ed_form, email, phone from " + stud_table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			T *s = new T();
			s->setStudentId(S2WS(string((char *)sqlite3_column_text(stmt, 0))));
			s->setName(S2WS(string((char *)sqlite3_column_text(stmt, 1))));
			s->setSurname(S2WS(string((char *)sqlite3_column_text(stmt, 2))));
			s->setPatronomic(S2WS(string((char *)sqlite3_column_text(stmt, 3))));
			s->setEdForm(S2WS(string((char *)sqlite3_column_text(stmt, 4))));
			s->setEmail(S2WS(string((char *)sqlite3_column_text(stmt, 5))));
			s->setPhone(S2WS(string((char *)sqlite3_column_text(stmt, 6))));

			result.push_back(s);

			sqlite3_step(stmt);
		}

	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

template<class T>
inline map<wstring, vector<wstring>> DataBase<T>::getGroup2V()
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	map<wstring, vector<wstring>> result;


	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select * from " + group_table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			vector<wstring> tmp;

			wstring key = S2WS(string((char *)sqlite3_column_text(stmt, 0)));
			
			for (int j =1; sqlite3_column_text(stmt, j); j++)
				tmp.push_back(S2WS(string((char *)sqlite3_column_text(stmt, j))));

			result[key] = tmp;
			sqlite3_step(stmt);
		}
		if (!result.size())
		{
			wcout << L"SELECT ERROR: Table '" << S2WS(group_table) << "' is Empty.'" << endl;
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

template<class T>
inline vector<pair<int, vector<int>>> DataBase<T>::getMarks2VById(wstring student_id)
{
	/*
		Get studetn_id 
		return: {	
					{term, {marks ...}}, 
					{term, {marks ...}}
				};
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<pair<int, vector<int>>> result;

	vector<wstring> cols = getColNames(S2WS(mark_table));
	wstring str_cols;

	for (int i = 0; i < cols.size(); i++)
	{
		str_cols = str_cols + S2WS(mark_table) + L"." + cols[i];

		if (i < cols.size() - 1)
			str_cols = str_cols + L",";
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		//"select * from students as s inner join marks as m on s.student_id = m.student_id where s.student_id like '07360022';"
		string sql("select " + WS2S(str_cols) + " from " + stud_table + " as s inner join " + mark_table + " on s.student_id = marks.student_id where s.student_id = '" + WS2S(student_id) + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			vector<int> tmp;

			wstring student_id = S2WS(string((char *)sqlite3_column_text(stmt, 0)));
			int term = sqlite3_column_int(stmt, 1);

			for (int j = 2; sqlite3_column_text(stmt, j); j++)
				tmp.push_back(sqlite3_column_int(stmt, j));

			result.push_back(make_pair(term, tmp));
			sqlite3_step(stmt);
		}
		if (!result.size())
		{
			//wcout << L"SELECT ERROR: Table '" << S2WS(mark_table) << "' is Empty.'" << endl;
			return {};
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

template<class T>
inline vector<wstring> DataBase<T>::getColNames(wstring table)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	vector<wstring> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("pragma table_info(" + WS2S(table) + ");");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);

		while (sqlite3_column_text(stmt, 0))
		{
			result.push_back(S2WS(string((char *)sqlite3_column_text(stmt, 1))));
			sqlite3_step(stmt);
		}

	}
	else
	{
		cout << "Failed to open db\n";
	}

	sqlite3_close(db);

	return result;
}

template<class T>
inline Student * DataBase<T>::getStudentById(wstring id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table = "students";

	Student* s = new Student();

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select student_id, first_name, last_name, patronymic, ed_form, email, phone from " + table +
					"where student_id = '" + WS2S(id) + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			s->setStudentId(S2WS(string((char *)sqlite3_column_text(stmt, 0))));
			s->setName(S2WS(string((char *)sqlite3_column_text(stmt, 1))));
			s->setSurname(S2WS(string((char *)sqlite3_column_text(stmt, 2))));
			s->setPatronomic(S2WS(string((char *)sqlite3_column_text(stmt, 3))));
			s->setEdForm(S2WS(string((char *)sqlite3_column_text(stmt, 4))));
			s->setEmail(S2WS(string((char *)sqlite3_column_text(stmt, 5))));
			s->setPhone(S2WS(string((char *)sqlite3_column_text(stmt, 6))));

			sqlite3_step(stmt);
		}

	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return s;
}
