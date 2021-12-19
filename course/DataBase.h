#pragma once
#include <locale>
#include <codecvt>
#include <string>

#include "Header.h"
#include "sqlite/sqlite3.h"
#include "User.h"
#include "Stipend.h"
#include "Convert.h"

using namespace Convert;
using namespace std;

class Admin;
class Student;

/*----------------Class DataBase--------------------*/
class DataBase {
private: 
	string db_path = "./migrate/main.db";

	string admin_table = "admin";
	string user_table = "users";
	string stud_table = "students";
	string mark_table = "marks";
	string group_table = "groups";
	string univ_group_table = "university_groups";
	string univ_spec_table = "university_specialities";
	string univ_fac_table = "university_faculties";
	string addit_stipend = "additional_stipend";
	string student_addit_stipend = "students_addit_stipend";

public:
	string getDBPath() { return db_path; }

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
	vector<Faculty *> getFaculties();
	vector<Speciality *> geSpecialities(int fac_id);
	vector<Group *> getGroups(int fac_id = -1, int spec_id = -1);
	/*------ University funcs ------*/

	/*-----Student------*/
	int AddNoteStudent(Student *s);
	int AddNoteStudentGroup(Student *s);
	int AddMarks(vector<int>, vector<wstring>, wstring);
	int updateGroup(wstring student_id, wstring & update_str);
	vector<Student*> getStudents();
	map<wstring, vector<wstring>> getGroup2V(wstring student_id = L"");
	vector<pair<pair<int, bool>, vector<int>>> getMarks2VById(wstring);
	Student * getStudentById(wstring id);
	wstring getStudentIdByUser(User * s);
	template <class T>
	int DelNoteByStydentId(wstring id, T s);
	/*-----Student------*/

	/*-----Additiontal stipends------*/
	vector<Stipend*> getAdditStipends();
	vector<Stipend*> getStudentAdditStipends(wstring student_id = L"");
	int AddNoteStudentStipend(wstring student_id, int stipend_id, int term);
	/*-----Additiontal stipends------*/

	vector<wstring> getColNames(wstring table);

};
/*----------------End Class DataBase----------------*/


inline
int DataBase::existStudent(wstring student_id)
{
	/*
		return: кол-во ответов при запросе student_id	
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	int res = 0;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("select count(*) from " + table + " where login like '" + l + "' and password like '" + pass + "';");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		res = sqlite3_column_int(stmt, 0);
	}
	else
	{
		wcout << "Failed to open db\n";
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("select * from " + table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			T *s = new T;
			s->setLogin(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0)));
			s->setPassword(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));

			if (sqlite3_column_text(stmt, 2)) {
				s->setStudentId(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));
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
inline int DataBase::updateTable(T s, wstring update_str)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("pragma foreign_keys=on;"
			"insert into "+ user_table + "(login, password, student_id) values ('" + WS2S(s->getLogin()) +
			"', '" + WS2S(s->getEncrPassword()) + "', '" + WS2S(s->getStudentId()) + "');");

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
		return 0;
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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
		return 0;
	}

	sqlite3_close(db);
	return 1;
}

inline vector<Faculty *> DataBase::getFaculties()
{
	/*
		return: {id, {abbrev, name}}
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	vector<Faculty *> result;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("select id, abbrev, name from " + univ_fac_table + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{	
			Faculty * fac = new Faculty;

			fac->setId(sqlite3_column_int(stmt, 0));
			fac->setAbbrev(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			fac->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));

			result.push_back(fac);

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

inline vector<Speciality *> DataBase::geSpecialities(int fac_id)
{
	/*
		return: {spec_id, {spec_abbrev, spec_name}},
		. . .
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	string table;
	vector<Speciality *> result;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("select id, abbrev, name from " + univ_spec_table + " where facultyId = " + to_string(fac_id) + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			Speciality * spec = new Speciality;

			spec->setId(sqlite3_column_int(stmt, 0));
			spec->setAbbrev(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			spec->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 2)));

			result.push_back(spec);

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

inline vector<Group *> DataBase::getGroups(int fac_id, int spec_id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	string sql;
	vector<Group *> result;

	if (fac_id == -1 and spec_id == -1)
	{
		sql = "select name, course from " + univ_group_table + ";";
	}
	else
	{
		sql = "select name from " + univ_group_table + " where facultyId = " + to_string(fac_id) + " and specialityId = " + to_string(spec_id) + ";";

	}

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			Group * gr = new Group;

			gr->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 0)));

			result.push_back(gr);
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


	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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


	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		wstring info = L"'" + s->getStudentId() + L"'," + L"'" + s->getGroup().getName() + L"'," + L"'" + s->getFaculty().getAbbrev() + L"'," + L"'" + s->getSpec().getAbbrev() +  L"'";

		string sql("pragma foreign_keys=on;"
			"insert into " + group_table + " values (" + WS2S(info) + ");");

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
		return 0;
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

inline int DataBase::updateGroup(wstring student_id, wstring & update_str)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		wcout << update_str << endl;
		wcout << S2WS(WS2S(update_str)) << endl;
		string sql("update " + group_table + " set " + WS2S(update_str) + " where student_id = '" + WS2S(student_id) + "';");

		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			//wcout << S2WS(err) << endl;
			return 0;
		}
	}
	else
	{
		cout << "Failed to open db\n";
		return -1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 1;
}

inline 
vector<Student*> DataBase::getStudents()
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<Student*> result;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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
vector<Stipend*> DataBase::getAdditStipends()
{
	/*
		params: no
		return: vector of Stipend objs
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<Stipend *> result;
	string sql;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		string sql("select id, name, ratio from " + addit_stipend + ";");

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); //executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			Stipend * tmp_st = new Stipend;

			tmp_st->setId(sqlite3_column_int(stmt, 0));
			tmp_st->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			tmp_st->setRatio(sqlite3_column_double(stmt, 2));

			result.push_back(tmp_st);
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
vector<Stipend*> DataBase::getStudentAdditStipends(wstring student_id)
{
	/*
		params: student_id, default none
		return: vector of Stipend objs
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;

	vector<Stipend *> result;
	string sql;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		if (student_id.length())
			sql = "select a.id, a.name, a.ratio, sas.term from " + addit_stipend + " as a inner join " + student_addit_stipend + " as sas " 
			"on a.id = sas.stipend_id where sas.student_id = '" + WS2S(student_id) + "';";
		else
			sql = "select a.id, a.name, a.ratio, sas.term from " + addit_stipend + " as a inner join " + student_addit_stipend + " as sas "
			"on a.id = sas.stipend_id;";

		sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL); //preparing the statement
		sqlite3_step(stmt); // executing the statement

		while (sqlite3_column_text(stmt, 0))
		{
			Stipend * tmp_st = new Stipend;

			tmp_st->setId(sqlite3_column_int(stmt, 0));
			tmp_st->setName(static_cast<const wchar_t*>(sqlite3_column_text16(stmt, 1)));
			tmp_st->setRatio(sqlite3_column_double(stmt, 2));
			tmp_st->setTerm(sqlite3_column_int(stmt, 3));

			result.push_back(tmp_st);
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
int DataBase::AddNoteStudentStipend(wstring student_id, int stipend_id, int term)
{
	/*
		Func adds info about the assigned stipend for the students.

		return: 1 - good auth;
				0 - faild auth;
				-1 - faild opening db.
	*/

	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;


	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
	{
		wstring info = L"'" + student_id + L"', " + to_wstring(stipend_id) + L", " + to_wstring(term);

		string sql("pragma foreign_keys=on;"
			"insert into " + student_addit_stipend + " values (" + WS2S(info) + ");");

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
vector<wstring> DataBase::getColNames(wstring table)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	vector<wstring> result;

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return result;
}

inline 
Student * DataBase::getStudentById(wstring id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;

	Student* s = new Student();

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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

	if (sqlite3_open(getDBPath().c_str(), &db) == SQLITE_OK)
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
