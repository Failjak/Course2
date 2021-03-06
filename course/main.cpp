#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "LoginController.h"
#include "AdminController.h"
#include "UserController.h"
#include "Admin.h"
#include "User.h"
#include "Menu.h"
#include "Convert.h"

/*
select list_name from university_groups; 
	-- ???????? ??? ?????? (??????????? int, ?? ????????? ????)


select list_name from university_groups where 
list_specialityDepartmentEducationFormId = '20072';
	-- ???????? ??? ????????? ?????? ?? id ?????????????


select * from university_faculties ;
	-- ???????? ??? ??????????
*/

using namespace Convert;
using namespace std;

void create_table() 
{
	DataBase s;

	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	string table = "user";

	if (sqlite3_open(s.getDBPath().c_str(), &db) == SQLITE_OK)
	{
		/*string sql("create table students_marks("
			"student_id text not null,"
			"student_id_marks text not null,"
			"FOREIGN key (student_id) REFERENCES students(student_id) on delete CASCADE on update no action,"
			"FOREIGN key (student_id_marks) REFERENCES marks(student_id) on delete CASCADE on update no action"
			");");*/

		/*string sql("CREATE TABLE students("
			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
			"first_name TEXT NOT NULL,"
			"last_name TEXT NOT NULL,"
			"patronymic TEXT NOT NULL,"
			"ed_form text check(ed_form in ('C', 'F')) not null default 'F',"
			"email TEXT NOT NULL UNIQUE,"
			"phone TEXT NOT NULL UNIQUE,"
			"FOREIGN KEY(student_id) REFERENCES users(student_id) ON DELETE CASCADE);");*/

		/*string sql("create table users("
					"login text not null,"
					"password text not null,"
					"student_id text CHECK(length(student_id) = 8) PRIMARY KEY not null);");*/

		/*string sql("CREATE TABLE groups("
			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
			"group_number text,"
			"faculty text not null,"
			"spec text not null,"
			"FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE"
			");");*/

		/*string sql("create table marks("
					"student_id text CHECK(length(student_id) = 8),"
					"term INTEGER not null,"
					"retake INTEGER not null,"
					"Math INTEGER not null,"
					"OOP INTEGER not null,"
					"Philosophy INTEGER not null,"
					"CN INTEGER not null,"
					"Economic INTEGER not null"
					");");*/

		string sql("create table additional_stipend("
			"id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
			"name text not null,"
			"ratio real not null"
			");");

		/*string sql("create table students_addit_stipend("
			"student_id text not null,"
			"stipend_id int not null,"
			"term int not null,"
			"FOREIGN key (student_id) REFERENCES students(student_id) on delete CASCADE on update no action,"
			"FOREIGN key (stipend_id) REFERENCES additional_stipend(id) on delete CASCADE on update no action"
			");");*/


		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);

		if (rc != SQLITE_OK)
		{
			wcout << L"ERROR:" <<S2WS(err) << endl;
		}
	}
	else
	{
		cout << "Failed to open db\n";
	}

	sqlite3_close(db);
}

int main(int argc, char* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	//create_table();

	int flag = 1;

	while (flag)
	{
		system("cls");
		switch (type_menu())
		{
		case 1:
		{
			Admin admin;
			LoginController<Admin> lC;

			system("cls");
			if (lC.checkAuth(&admin))
			{
				system("cls");
				wcout << L"???? ???????? ???????.\n" << endl;
				AdminController::main(&admin);
			}
			break;
		}
		case 2:
		{
			User user;
			LoginController<User> lC;

			system("cls");
			if (lC.checkAuth(&user))
			{
				system("cls");
				wcout << L"???? ???????? ???????." << endl;
				UserController::main(&user);
			}
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			wcout << L"???????? ?????." << endl;
			break;
		}
		}
	}

	return 0;
}

