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

	coutTitle(L"���������� ������������");

//	system("chcp 1251");

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

	if (db.AddNoteStudent(&student))
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

	/*
		��������� ����� ���� ���� � �������(���� �� ��������� ����� �������
			�� ����� ���������� � ������ �� ������ �����, ����������, �������������)
		����� ���� �������� �������� ���� �� ������ ����-�� � ������ ������ ������
		���������� � ������, � ��� ����-����!!!
	*/

	if (!db.existStudent(student_id))
	{
		wcout << L"������ �������� �� ����������." << endl;
		return -1;
	}

	vector<wstring> cols = db.getColNames(L"marks");
	vector<int> marks;

	wcout << L"������� ������ �� ���������:" << endl;
	for (int i = 2; i < cols.size(); i++) // bacause first&sec elem is student_id and term
	{
		int num;

		wcout << DBfield_subj.at(cols.at(i)) << L": ";
		CIN_FLUSH;
		cin >> num;
		marks.push_back(num);

		/*try
		{
			wcout << DBfield_subj.at(cols.at(i)) << L": ";
			cin >> num;
			marks.push_back(num);
		}
		catch (int)
		{
					
			std::wcerr << L"We caught an int exception with value: " << endl;
		}*/
	}

	//DBfield_subj.at(L"Math");

	return 0;
}
