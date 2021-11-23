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
	vector<User *> users = db.getObj2V();

	for (int i =0 ; i< users.size(); i++)
		users[i]->setStudent(db.getStudentById(users[i]->getStudentId()));

	return users;
}

int Admin::AddUser()
{
	/*
		return: 1 - no exeption;
				0 - faild insert.
	*/

	DataBase<User> db;
	wstring login, password, student_id;

	coutTitle(L"���������� ������������");

	wcout << L"������� �����: ";
	wcin >> login;
	wcout << L"������� ������: ";
	wcin >> password;
	wcout << L"������� ����� �������������: ";
	wcin >> student_id;

	User user(login, password, student_id);

	if (db.exist(&user))
	{
		wcout << L"����� ������������ ��� ����������." << endl;
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

int Admin::AddStudent()
{
	/*
		return: 1 - no exeption;
				0 - faild insert.
	*/

	DataBase<Student> db;
	wstring last_name, patr, first_name, student_id, ed_form, email, phone;
	wstring group, faculty, spec;

	coutTitle(L"���������� ������������");

	wcout << L"������� ID ��������: ";
	wcin >> student_id;
	wcout << L"������� ���: ";
	wcin >> first_name;
	wcout << L"������� �������: ";
	wcin >> last_name;
	wcout << L"������� ��������: ";
	wcin >> patr;
	wcout << L"������� ����� ������: ";
	wcin >> group;
	wcout << L"������� ���������: ";
	wcin >> faculty;
	wcout << L"������� �������������: ";
	wcin >> spec;
	wcout << L"������� ����� �������� (F - ������, � - ������): ";
	wcin >> ed_form;
	wcout << L"������� email: ";
	wcin >> email;
	wcout << L"������� �������: ";
	wcin >> phone;

	Student student(student_id, first_name, last_name, patr, group, faculty, spec, email, phone, ed_form);

	if (db.exist(&student))
	{
		wcout << L"����� ������������ ��� ����������." << endl;
		return -1;
	}

	/*if (db.AddNoteStudent(&Student) == 1)
	{
		return true;
	}*/

	return false;
}

int Admin::DelStudent(User * s)
{
	return 0;
}
