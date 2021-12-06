#pragma once
#include <locale>
#include <codecvt>
#include <string>

#include "Header.h"
#include "sqlite/sqlite3.h"

using namespace std;

class Admin;
class Student;
class User;

/*----------------Class DataBase--------------------*/
class DataBase {
private: 
	string admin_table = "admin";
	string user_table = "users";
	string stud_table = "students";
	string mark_table = "marks";
	string group_table = "groups";
	string univ_group_table = "university_groups";
	string univ_spec_table = "university_specialities";
	string univ_fac_table = "university_faculties";

public:
	template <class T>
	int exist(T * s);

	template <class T>
	vector<T*> getObj2V(T s);

	template <class T>
	int updateTable(T s, wstring update_str);

	int existStudent(wstring student_id);
	int existMarks(wstring student_id, int term);
	
	/*-----Admin------*/
	int AddNoteUser(User *s);
	/*-----Admin------*/
	
	/*------ University funcs ------*/
	map<int, pair<wstring, wstring>> getFaculties();
	map<int, pair<wstring, wstring>> geSpecialities(int fac_id);
	vector<int> getGroups(int fac_id, int spec_id);
	/*------ University funcs ------*/

	/*-----Student------*/
	int AddNoteStudent(Student *s);
	int AddNoteStudentGroup(Student *s);
	int AddMarks(vector<int>, vector<wstring>, wstring);
	vector<Student*> getStudents();
	map<wstring, vector<wstring>> getGroup2V(wstring student_id = L"");
	vector<pair<pair<int, bool>, vector<int>>> getMarks2VById(wstring);
	Student * getStudentById(wstring id);
	wstring getStudentIdByUser(User * s);
	template <class T>
	int DelNoteByStydentId(wstring id, T s);
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
	using convert_typeX = codecvt_utf8_utf16<wchar_t>;
	wstring_convert<convert_typeX, wchar_t> converterX;

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

inline
int DataBase::existStudent(wstring student_id)
{
	/*
		return: кол-во ответов при запросе student_id	
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	int res = 0;

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

inline int DataBase::existMarks(wstring student_id, int term)
{
	/*
		params: student_id, term
		return: кол-во совпадний в таблице, с таким student_id and term
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	int res = 0;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select count(*) from " + mark_table + " where student_id like '" + WS2S(student_id) + "' and term =" + to_string(term) + ";");

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
inline
int DataBase::exist(T * s)
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
	pass = WS2S(s->getEncrPassword());

	int res = 0;
	string table;

	if (is_same<T, Admin>::value)
	{
		table = admin_table;
	}
	else if (is_same<T, User>::value) {
		table = user_table;
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
inline vector<T*> DataBase::getObj2V(T s)
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
		table = admin_table;
	}
	else if (is_same<T, User>::value) {
		table = user_table;
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select * from " + table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			// static_cast<const char*>(sqlite3_column_text16(statement, index))
			T *s = new T;
			s->setLogin(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0)));
			s->setPassword(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));

			if (sqlite3_column_text(stmt, 2)) {
				s->setStudentId(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));
			}

			/*s->setLogin(S2WS(string((char *)sqlite3_column_text(stmt, 0))));
			s->setPassword(S2WS(string((char *)sqlite3_column_text(stmt, 1))));

			if (sqlite3_column_text(stmt, 2)){ 
				s->setStudentId(S2WS(string((char *)sqlite3_column_text(stmt, 2))));
			}*/

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
inline int DataBase::updateTable(T s, wstring update_str)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	vector<T*> result;

	if (is_same<T, Admin>::value)
	{
		table = admin_table;
	}
	else if (is_same<T, User>::value) {
		table = user_table;
	}
	else if (is_same<T, Student>::value) {
		table = stud_table;
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("update " + table + " set " +  WS2S(update_str) + " student_id = '" + WS2S(s.getStudentId()) + "';");

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
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

inline 
int DataBase::AddNoteUser(User * s)
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
			"', '" + WS2S(s->getEncrPassword()) + "', '" + WS2S(s->getStudentId()) + "');");

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
int DataBase::DelNoteByStydentId(wstring id, T s)
{
	/*
		Func delete note from Users or Students, by Student id 	
	*/

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
		string sql("pragma foreign_keys=on;"
			"delete from " + table + " where student_id = '" + WS2S(id) + "';");

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

inline map<int, pair<wstring, wstring>> DataBase::getFaculties()
{
	/*
		return: {id, {abbrev, name}}
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	map<int, pair<wstring, wstring>> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select id, abbrev, name from " + univ_fac_table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{	
			pair<wstring, wstring> tmp( static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)),
				static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)) );

			result[sqlite3_column_int(stmt, 0)] = tmp;
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

inline map<int, pair<wstring, wstring>> DataBase::geSpecialities(int fac_id)
{
	/*
		return: {spec_id, {spec_abbrev, spec_name}},
		. . .
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	map<int, pair<wstring, wstring>> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select id, abbrev, name from " + univ_spec_table + " where facultyId = " + to_string(fac_id) + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			pair<wstring, wstring> tmp(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)),
				static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));

			result[sqlite3_column_int(stmt, 0)] = tmp;
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

inline vector<int> DataBase::getGroups(int fac_id, int spec_id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	vector<int> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select name from " + univ_group_table + " where facultyId = " + to_string(fac_id) + " and specialityId = " + to_string(spec_id) + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			result.push_back(sqlite3_column_int(stmt, 0));
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

inline
int DataBase::AddNoteStudent(Student * s)
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

inline 
int DataBase::AddNoteStudentGroup(Student * s)
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
		wstring info = L"'" + s->getStudentId() + L"'," + L"'" + s->getGroup() + L"'," + L"'" + s->getFaculty() + L"'," + L"'" + s->getSpec() +  L"'";

		string sql("pragma foreign_keys=on;"
			"insert into " + group_table + " values (" + WS2S(info) + ");");

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

inline 
int DataBase::AddMarks(vector<int> marks, vector<wstring> subj, wstring student_id)
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

	string str_cols, str_marks;

	for (int i = 0; i < subj.size(); i++)
	{
		str_marks += to_string(marks[i]);

		str_cols += WS2S(subj[i]);

		if (i < subj.size() - 1)
		{
			str_cols += ",";
			str_marks += ",";
		}
	}

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("pragma foreign_keys=on;"
			"insert into " + mark_table + " (student_id, " + str_cols + ") values('" + WS2S(student_id) + "', " + str_marks + ");");

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

inline 
vector<Student*> DataBase::getStudents()
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<Student*> result;

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select student_id, first_name, last_name, patronymic, ed_form, email, phone from " + stud_table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			Student *s = new Student();
			s->setStudentId(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0)));
			s->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			s->setSurname(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));
			s->setPatronomic(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 3)));
			s->setEdForm(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 4)));
			s->setEmail(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 5)));
			s->setPhone(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 6)));

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

inline 
map<wstring, vector<wstring>> DataBase::getGroup2V(wstring student_id)
{
	/*
		params: student_id(optional)
		return: map{student_id, {group, fac, spec, ...}}
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	map<wstring, vector<wstring>> result;
	string sql;

	if (student_id.length())
		sql = ("select * from " + group_table + " where student_id = '" + WS2S(student_id) + "';");
	else
		sql = ("select * from " + group_table + ";");

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			vector<wstring> tmp;

			wstring key = static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0));
			
			for (int j =1; sqlite3_column_text(stmt, j); j++)
				tmp.push_back(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, j)));

			result[key] = tmp;
			sqlite3_step(stmt);
		}
		if (!result.size())
		{
			//wcout << L"SELECT ERROR: Table '" << S2WS(group_table) << "' is Empty.'" << endl;
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

inline 
vector<pair<pair<int, bool>, vector<int>>> DataBase::getMarks2VById(wstring student_id)
{
	/*
		Get student_id 
		return: {	
					{term, {retake, marks ...}}, 
					{term, {retake, marks ...}}
				};
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<pair<pair<int, bool>, vector<int>>> result;

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

			wstring student_id = static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0));
			int term = sqlite3_column_int(stmt, 1);
			bool retake = sqlite3_column_int(stmt, 2);

			for (int j = 3; sqlite3_column_text(stmt, j); j++)
				tmp.push_back(sqlite3_column_int(stmt, j));

			pair<int, bool> term_retake = {term, retake};
			result.push_back(make_pair(term_retake, tmp));
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

inline 
vector<wstring> DataBase::getColNames(wstring table)
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
			result.push_back(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
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

inline 
Student * DataBase::getStudentById(wstring id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	Student* s = new Student();

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select student_id, first_name, last_name, patronymic, ed_form, email, phone from " + stud_table +
					" where student_id = '" + WS2S(id) + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		int flag = 1;

		while (sqlite3_column_text(stmt, 0))
		{
			flag = 0;
			s->setStudentId(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0)));
			s->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			s->setSurname(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));
			s->setPatronomic(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 3)));
			s->setEdForm(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 4)));
			s->setEmail(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 5)));
			s->setPhone(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 6)));

			sqlite3_step(stmt);
		}
		if(flag) 
		{
			//wcout << L"Ошибка считывания студента." << endl;
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

inline wstring DataBase::getStudentIdByUser(User * s)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	wstring student_id = L"";

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		string sql("select student_id from " +  user_table +
			" where login = '" + WS2S(s->getLogin()) + "' and password = '" + WS2S(s->getEncrPassword()) + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		for (; sqlite3_column_text16(stmt, 0); sqlite3_step(stmt))
			student_id = static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0));
	}
	else
	{
		cout << "Failed to open db\n";
		return {};
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return student_id;
}
