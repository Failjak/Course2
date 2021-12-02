#include <conio.h>
#include <ctime>

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


vector<int> Admin::addMarks2V(wstring student_id, int course, vector<wstring> subjs)
{
	DataBase db;
	vector<int> marks;
	int ch;
	wstring num =L"";

	if (db.existMarks(student_id, course * 2))
	{
		wcout << L"������� �� ��� �������� ��������." << endl;
	}

	wcout << L"������� �� �������: ";
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
			if (stoi(num + (wchar_t)ch) > 0 and stoi(num + (wchar_t)ch) <= course * 2)
			{
				wcout << (wchar_t)ch;
				num += (wchar_t)ch;
				if (!db.existMarks(student_id, stoi(num))) { break; }
			}
		}
	} while (true);
	marks.push_back(stoi(num));

	wcout << L"\n���������(1-'��', 0-'���'): ";
	while (true)
	{
		num = L"";
		ch = _getch();
		if (ch == 13 and num.length() > 0) { break; }
		if (ch == 32) { continue; }
		if (ch == 8 and num.length() > 0)
		{
			wcout << (wchar_t)8 << ' ' << wchar_t(8);
			num.erase(num.length() - 1, num.length());
		}
		else if (ch == 48 or ch == 49)
		{
			wcout << (wchar_t)ch;
			num += (wchar_t)ch;
			break;
		}
	}
	marks.push_back(stoi(num));

	wcout << L"\n������� ������ �� ���������:" << endl;
	for (int i = 2; i < subjs.size(); i++) // skip term and retake
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

vector<Student*> Admin::getStudents2V(wstring student_id)
{
	/*
		schema marks: student_id: {term, retake, subjs ...}
		get: student_id, �������, �� �������� ���� �������� ���������
		return: vector<student *> � ������������ ������ (��������� ���������, ��������� ��������� �������)
	*/

	vector<Student *> students;
	map<wstring, vector<wstring>> groups;
	vector<pair<pair<int, bool>, vector<int>>> marks;
	vector<wstring> subj;
	vector<bool> retake;
	DataBase db;

	if (student_id.length())
	{
		if (!db.existStudent(student_id))
		{
			wcout << L"������ �������� �� ����������." << endl;
			return {};
		}
		students.push_back(db.getStudentById(student_id));
	}
	else
		students = db.getStudents2V();

	groups = db.getGroup2V();

	for (int i = 0; i < students.size(); i++)
	{
		wstring student_id = students.at(i)->getStudentId();

		marks = db.getMarks2VById(student_id);// ������� ������ � ������� ��������� � ������� �� ����
		if (marks.size())
		{
			subj = db.getColNames(L"marks");
			subj.erase(subj.begin(), subj.begin() + 3); // del 'student_id'&'term'&'retake' from subjects
		}

		students.at(i)->setCourse(calcCourse(student_id));
		students.at(i)->setMarks(marks, subj);
		students.at(i)->calcStipend(students.at(i));
	}
	mergeStGr(&students, groups, L"group");

	return students;
}

vector<User*> Admin::getUsers2V()
{
	DataBase db;
	vector<User *> users = db.getObj2V(User());

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

	DataBase db;
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
	DataBase db;
	if (db.DelNoteByStydentId(s->getStudentId(), User()) == 1)
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

	DataBase db;
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

	if (db.existStudent(student.getStudentId()))
	{
		wcout << L"����� ������������ ��� ����������." << endl;
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
	DataBase db;
	if (db.DelNoteByStydentId(s->getStudentId(), Student()) == 1)
	{
		return 1;
	}

	return 0;
}

int Admin::AddMarksToStudent(Student * s)
{
	DataBase db;
	wstring student_id = s->getStudentId();

	vector<wstring> cols = db.getColNames(L"marks");
	cols.erase(cols.begin()); // del 'student_id' from subjects
	vector<int> marks;
	marks = addMarks2V(student_id, s->getCourse(), cols);

	if (db.AddMarks(marks, cols, student_id))
	{
		return 1;
	}

	return 0;
}

int Admin::AddMarksToStudent(wstring student_id)
{
	DataBase db;

	if (!db.existStudent(student_id))
	{
		wcout << L"������ �������� �� ����������." << endl;
		return -1;
	}

	vector<wstring> cols = db.getColNames(L"marks");
	Student * student = db.getStudentById(student_id);

	cols.erase(cols.begin()); // del 'student_id' from subjects
	vector<int> marks;
	marks = addMarks2V(student_id,student->getCourse(),cols);

	if (db.AddMarks(marks, cols, student_id))
	{
		return 1;
	}

	return 0;
}