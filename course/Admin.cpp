#include "Admin.h"
#include "Header.h"

void Admin::mergeStGr(vector<Student *> * st, map<wstring, vector<wstring>> b, wstring mode) 
{
	wstring key;

	for (int i = 0; i < st->size(); i++)
	{
		key = st->at(i)->getStudentId();
		map<wstring, vector<wstring>>::const_iterator pos = b.find(key);
		if (pos != b.end()) {
			if (mode == L"group")
			{
				st->at(i)->setGroup(pos->second.at(0));
				st->at(i)->setFaculty(pos->second.at(1));
				st->at(i)->setSpec(pos->second.at(2));
			}
			else if (mode == L"mark")
			{
				st->at(i)->setMarks(pos->second);
			}
		}
	}
}

vector<Student*> Admin::getStudents2V()
{
	vector<Student *> students;
	map<wstring, vector<wstring>> groups;
	map<wstring, vector<wstring>> marks;
	DataBase<Student> db;

	students = db.getStudents2V();
	groups = db.getGrpOrMark2V(L"group");
	marks = db.getGrpOrMark2V(L"mark");
	marks[L"subj"] = db.getColNames(L"marks");

	mergeStGr(&students, groups, L"group");
	mergeStGr(&students, marks, L"mark");

	return students;
}

vector<User*> Admin::getUsers2V()
{
	DataBase<User> db;

	return db.getObj2V();
}

int Admin::AddUser()
{
	/*
		return: 1 - no exeption;
				0 - faild insert.
	*/

	DataBase<User> db;
	wstring login, password;

	coutTitle(L"Добавление пользователя");

	wcout << L"Введите логин: ";
	wcin >> login;
	wcout << L"Введите пароль: ";
	wcin >> password;

	User user(login, password);

	if (db.exist(&user))
	{
		wcout << L"Такой пользователь уже существует." << endl;
		return -1;
	}

	if (db.AddNoteUser(&user) == 1)
	{
		return true;
	}

	return false;
}

int Admin::DelUser(User * s)
{
	DataBase<User> db;
	if (db.DelNoteUser(s) == 1)
	{
		return 1;
	}

	return 0;
}
