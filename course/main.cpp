#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "LoginController.h"
#include "LoginController.cpp"
#include "AdminController.h"
#include "UserController.h"
#include "Admin.h"
#include "User.h"
#include "Menu.h"

/*
select list_name from university_groups; 
	-- получить все группы (обязательно int, тк съедается нуль)


select list_name from university_groups where 
list_specialityDepartmentEducationFormId = '20072';
	-- получить все возможные группы по id специальности


select * from university_faculties ;
	-- получить все факультеты
*/

using namespace std;

//void create_table() 
//{
//	sqlite3 *db;
//	sqlite3_stmt * stmt;
//	char *err;
//
//	string table = "user";
//
//	if (sqlite3_open(DB_PATH, &db) == SQLITE_OK)
//	{
//		/*string sql("create table students_marks("
//			"student_id text not null,"
//			"student_id_marks text not null,"
//			"FOREIGN key (student_id) REFERENCES students(student_id) on delete CASCADE on update no action,"
//			"FOREIGN key (student_id_marks) REFERENCES marks(student_id) on delete CASCADE on update no action"
//			");");*/
//
//		/*string sql("CREATE TABLE students("
//			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
//			"first_name TEXT NOT NULL,"
//			"last_name TEXT NOT NULL,"
//			"patronymic TEXT NOT NULL,"
//			"ed_form text check(ed_form in ('C', 'F')) not null default 'F',"
//			"email TEXT NOT NULL UNIQUE,"
//			"phone TEXT NOT NULL UNIQUE,"
//			"FOREIGN KEY(student_id) REFERENCES users(student_id) ON DELETE CASCADE);");*/
//
//		/*string sql("create table users("
//					"login text not null,"
//					"password text not null,"
//					"student_id text CHECK(length(student_id) = 8) PRIMARY KEY not null);");*/
//
//		/*string sql("CREATE TABLE groups("
//			"student_id text CHECK(length(student_id) = 8) PRIMARY KEY,"
//			"group_number text,"
//			"faculty text not null,"
//			"spec text not null,"
//			"FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE"
//			");");*/
//
//		string sql("create table marks("
//					"student_id text CHECK(length(student_id) = 8),"
//					"term INTEGER not null,"
//					"retake INTEGER not null,"
//					"Math INTEGER not null,"
//					"OOP INTEGER not null,"
//					"Philosophy INTEGER not null,"
//					"CN INTEGER not null,"
//					"Economic INTEGER not null"
//					");");
//
//		int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &err);
//
//		if (rc != SQLITE_OK)
//		{
//			wcout << L"ERROR:" <<S2WS(err) << endl;
//		}
//	}
//	else
//	{
//		cout << "Failed to open db\n";
//	}
//
//	sqlite3_close(db);
//}

int main(int argc, char* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	int flag = 1;

	while (flag)
	{
		system("cls");
		switch (type_menu())
		{
		case 1:
		{
			Admin admin;
			LoginController<Admin> lContr;

			system("cls");
			if (lContr.chekAuth(&admin))
			{
				system("cls");
				wcout << L"Вход выполнен успешно.\n" << endl;
				AdminController::main(&admin);
			}
			break;
		}
		case 2:
		{
			User user;
			LoginController<User> lContr;

			system("cls");
			if (lContr.chekAuth(&user))
			{
				system("cls");
				wcout << L"Вход выполнен успешно." << endl;
				UserController::main(&user);
			}
			break;
		}
		case 0:
		{
			
		}
		default:
		{
			wcout << L"Неверный выбор." << endl;
			break;
		}
		}
	}

	return 0;
}

