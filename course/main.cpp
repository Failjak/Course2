#include <iostream>
#include <Windows.h>

#include "LoginController.h"
#include "LoginController.cpp"
#include "AdminController.h"
#include "Admin.h"
#include "User.h"
#include "Menu.h"


using namespace std;

void create_table() 
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	char *err;

	string table = "user";

	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
	{
		/*string sql("create table students_groups("
			"student_id text not null,"
			"student_id_g text not null,"
			"FOREIGN key (student_id) REFERENCES students(student_id) on delete CASCADE on update no action,"
			"FOREIGN key (student_id_g) REFERENCES groups(student_id) on delete CASCADE on update no action"
			");");*/

		/*string sql("CREATE TABLE students("
			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
			"first_name TEXT NOT NULL,"
			"last_name TEXT NOT NULL,"
			"patronymic TEXT NOT NULL,"
			"ed_form text check(ed_form in ('C', 'F')) not null default 'F',"
			"email TEXT NOT NULL UNIQUE,"
			"phone TEXT NOT NULL UNIQUE,"
			"FOREIGN KEY(student_id) REFERENCES users(student_id));");*/

		string sql("create table users("
					"login text not null,"
					"password text not null,"
					"student_id text CHECK(length(student_id) = 8) PRIMARY KEY not null);");

		/*string sql("CREATE TABLE groups("
			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
			"group_number text,"
			"faculty text not null,"
			"spec text not null,"
			"FOREIGN KEY (student_id) REFERENCES students(student_id)"
			");");*/

		/*string sql("create table marks("
					"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
					"math INTEGER not null,"
					"oop INTEGER not null,"
					"philosophy INTEGER not null,"
					"CN INTEGER not null,"
					"economy INTEGER not null,"
					"FOREIGN KEY (student_id) REFERENCES students(student_id)"
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	locale::global(std::locale(".utf-8"));

	system("chcp 65001");
	system("cls");

	int flag = 1;

	//create_table();

	while (flag)
	{
		system("cls");
		//switch (type_menu())
		switch(1)
		{
		case 1:
		{
			Admin admin;
			LoginController<Admin> lContr;

			system("cls");
			AdminController::main(&admin);

			/*if (lContr.chekAuth(&admin))
			{
				system("cls");
				wcout << L"���� �������� �������.\n" << endl;
				AdminController::main(&admin);
			}*/
			break;
		}
		case 2:
		{
			LoginController<User> lContr;

			User user;
			system("cls");
			if (lContr.chekAuth(&user))
			{
				system("cls");
				wcout << L"���� �������� �������." << endl;
				//UserController(user);
			}
			break;
		}

		case 3:

			return 0;
			break;

		default:
			wcout << L"�������� �����." << endl;
			break;
		}
	}

	return 0;
}

