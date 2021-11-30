#include <conio.h>

#include "Admin.h"
#include "Header.h"

void Admin::mergeStGr(vector<Student *> * st, map<wstring, vector<wstring>> b, wstring mode) 
{
	wstring student_id;

	for (int i = 0; i < st->size(); i++)
	{
		student_id = st->at(i)->getStudentId();
		map<wstring, vector<wstring>>::const_iterator pos = b.find(student_id);

		if (b.count(student_id))  {
			if (mode == L"group")
			{
				st->at(i)->setGroup(pos->second.at(0));
				st->at(i)->setFaculty(pos->second.at(1));
				st->at(i)->setSpec(pos->second.at(2));
			}
		}
	}
}

vector<int> Admin::addMarks2V(wstring student_id, vector<wstring> subjs)
{
	DataBase<Student> db;
	vector<int> marks;
	int ch;
	wstring num;

	wcout << L"Отметки за семестр: ";
	do
	{
		if (num.length())
		{
			wcout << (wchar_t)8 << ' ' << wchar_t(8);
			num = L"";
		}

		ch = _getch();
		if (ch == 13 and num.length() > 0) { break; }
		if (ch == 32) { continue; }
		if (ch == 8 and num.length() > 0)
		{
			wcout << (wchar_t)8 << ' ' << wchar_t(8);
			num.erase(num.length() - 1, num.length());
		}
		else if (ch >= 48 and ch <= 57)
		{
			if (stoi(num + (wchar_t)ch) > 0 and stoi(num + (wchar_t)ch) < 9)
			{
				wcout << (wchar_t)ch;
				num += (wchar_t)ch;
			}
		}
	} while (db.existMarks(student_id, stoi(num)));
	marks.push_back(stoi(num));

	wcout << L"\nВведите оценки по предметам:" << endl;
	for (int i = 1; i < subjs.size(); i++)
	{
		num = L"";
		wcout << DBfield_subj.at(subjs.at(i)) << L": ";

		while (true)
		{
			ch = _getch();
			if (ch == 13 and num.length() > 0) { break; }
			if (ch == 32) { continue; }
			if (ch == 8 and num.length() > 0)
			{
				wcout << (wchar_t)8 << ' ' << wchar_t(8);
				num.erase(num.length() - 1, num.length());
			}
			else if (ch >= 48 and ch <= 57)
			{
				if (num.length() == 0 or (stoi(num + (wchar_t)ch) >= 0 and stoi(num + (wchar_t)ch) <= 10))
				{
					wcout << (wchar_t)ch;
					num += (wchar_t)ch;
				}
			}
		}
		wcout << endl;

		marks.push_back(stoi(num));
	}

	return marks;
}

vector<Student*> Admin::getStudents2V()
{
	/*
		schema marks: student_id: {term, subjs ...}
	*/
	
	vector<Student *> students;
	map<wstring, vector<wstring>> groups;
	vector<pair<int, vector<int>>> marks;
	vector<wstring> subj;
	DataBase<Student> db;

	students = db.getStudents2V();
	groups = db.getGroup2V();
	
	for (int i = 0; i < students.size(); i++)
	{
		wstring student_id = students.at(i)->getStudentId();

		marks = db.getMarks2VById(student_id);
		if (marks.size())
		{
			subj = db.getColNames(L"marks");
			subj.erase(subj.begin(), subj.begin()+2); // del 'student_id'&'tern' from subjects
		}

		students.at(i)->setMarks(marks, subj);
	}
	mergeStGr(&students, groups, L"group");

	return students;
}

vector<User*> Admin::getUsers2V()
{
	DataBase<User> db;
	vector<User *> users = db.getObj2V();

	for (int i = 0; i < users.size(); i++)
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

	coutTitle(L"Добавление пользователя");

	wcout << L"Введите логин: ";
	wcin >> login;
	wcout << L"Введите пароль: ";
	wcin >> password;
	wcout << L"Введите номер студенческого: ";
	wcin >> student_id;

	User user(login, password, student_id);

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
	if (db.DelNoteByStydentId(s->getStudentId()) == 1)
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

	coutTitle(L"Добавление пользователя");

	wcout << L"Введите ID студента: ";
	wcin >> student_id;
	wcout << L"Введите имя: ";
	wcin >> first_name;
	wcout << L"Введите фамилию: ";
	wcin >> last_name;
	wcout << L"Введите отчество: ";
	wcin >> patr;
	wcout << L"Введите номер группы: ";
	wcin >> group;
	wcout << L"Введите факультет: ";
	wcin >> faculty;
	wcout << L"Введите специальность: ";
	wcin >> spec;
	wcout << L"Введите форму обучения (F - бюджет, С - платно): ";
	wcin >> ed_form;
	wcout << L"Введите email: ";
	wcin >> email;
	wcout << L"Введите телефон: ";
	wcin >> phone;

	Student student(student_id, first_name, last_name, patr, group, faculty, spec, email, phone, ed_form);

	if (db.existStudent(student.getStudentId()))
	{
		wcout << L"Такой пользователь уже существует." << endl;
		return -1;
	}

	if (db.AddNoteStudent(&student) and db.AddNoteStudentGroup(&student))
	{
		return true;
	}

	return false;
}

int Admin::DelStudent(Student * s)
{
	DataBase<Student> db;
	if (db.DelNoteByStydentId(s->getStudentId()) == 1)
	{
		return 1;
	}

	return 0;
}

int Admin::AddMarksToStudent(Student * s)
{
	DataBase<Student> db;



	return 0;
}

int Admin::AddMarksToStudent(wstring student_id)
{
	DataBase<Student> db;

	if (!db.existStudent(student_id))
	{
		wcout << L"Такого студента не существует." << endl;
		return -1;
	}

	vector<wstring> cols = db.getColNames(L"marks");
	cols.erase(cols.begin()); // del 'student_id'&'tern' from subjects
	vector<int> marks;
	marks = addMarks2V(student_id, cols);

	if (db.AddMarks(marks, cols, student_id))
	{
		return 1;
	}

	return 0;
}
