#include "User.h"
#include "DataBase.h"
#include "Header.h"

using namespace std;

int User::calcCourse(wstring student_id)
{
	int course;
	time_t now = time(0);
	tm * ltm = localtime(&now);
	int cur_year = (1900 + ltm->tm_year) % 100;
	int cur_month = ltm->tm_mon + 1;
	int tmp = student_id.at(0) - 48;
	course = (cur_year - tmp) % 10 + 1;
	return course;
}

User::User(const User &tmp)
{
	this->login = tmp.login;
	this->password = tmp.password;
	this->student = tmp.student;
}

void User::setStudent()
{
	vector<wstring> group;
	vector<pair<pair<int, bool>, vector<int>>> marks;
	vector<wstring> subj;
	vector<bool> retake;
	DataBase db;

	if (student_id.length())
	{
		if (!db.existStudent(student_id))
		{
			wcout << L"Ошибка. Такого студента не существует." << endl;
			return;
		}
	}

	this->student = *db.getStudentById(student_id);

	try
	{
		group = db.getGroup2V(student_id).at(student_id);
		marks = db.getMarks2VById(student_id);
	}
	catch (std::out_of_range)
	{


	}
	if (marks.size())
	{
		subj = db.getColNames(L"marks");
		subj.erase(subj.begin(), subj.begin() + 3); // del 'student_id'&'term'&'retake' from subjects
	}

	this->student.setGroup(group.at(0));
	this->student.setFaculty(group.at(1));
	this->student.setSpec(group.at(2));

	this->student.setCourse(calcCourse(student_id));
	this->student.setMarks(marks, subj);
	this->student.calcStipend(&student);
}

wostream & operator<<(wostream & wcout, const User & user)
{
	int space_subjects = 0;
	int MIN_SPACE = 14;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	Student student = user.student;

	int max_size_FN = 0, max_size_fac = 0, max_size_spec = 0,
		max_size_group = 0, max_size_av_mark = 0, max_size_ed_form = 0,
		max_size_mail = 0, max_size_phone = 0,
		max_size_login = 0, max_size_pass = 0, max_size_id = 0;

	max_size_login = user.login.length();
	max_size_pass = user.password.length();
	max_size_id = user.student_id.length();
	max_size_FN = student.getFullName().length();
	max_size_fac = student.getFaculty().length();
	max_size_spec = student.getSpec().length();
	max_size_group = student.getGroup().length();
	max_size_av_mark = to_string(student.getAvgMark()).length();
	max_size_ed_form = student.getEdFormWstr().length();
	max_size_mail = student.getEmail().length();
	max_size_phone = student.getPhone().length();

	int table_width = space_subjects + (
		(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) +
		(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) +
		(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) +
		(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) +
		(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) +
		(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) +
		(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) +
		(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) +
		(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) +
		(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) +
		(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE));


	/*if (title.length())
	{
		int title_table_widht = (table_width - title.length()) / 2;
		wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
	}*/

	wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
	wcout << L"│";
	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);

	wcout
		<< setw(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) << left << L"Логин "
		<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << L"Пароль "
		<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << L"ID студента "
		<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << L"ФИО"
		<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << L"Факультет"
		<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << L"Спецальность"
		<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << L"Группа"
		<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << L"Ср. балл"
		<< setw(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) << left << L"Форма обучения "
		<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << L"Почта"
		<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << L"Телефон";


	SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	wcout << left << L"│" << endl;
	wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
	wcout << L"│"
		<< setw(max_size_login > MIN_SPACE ? max_size_login + 1 : MIN_SPACE) << left << user.login
		<< setw(max_size_pass > MIN_SPACE ? max_size_pass + 1 : MIN_SPACE) << left << Encrypt::decrypt(user.password)
		<< setw(max_size_id > MIN_SPACE ? max_size_id + 1 : MIN_SPACE) << left << user.student_id
		<< setw(max_size_FN > MIN_SPACE ? max_size_FN + 1 : MIN_SPACE) << left << student.getFullName()
		<< setw(max_size_fac > MIN_SPACE ? max_size_fac + 1 : MIN_SPACE) << left << student.getFaculty()
		<< setw(max_size_spec > MIN_SPACE ? max_size_spec + 1 : MIN_SPACE) << left << student.getSpec()
		<< setw(max_size_group > MIN_SPACE ? max_size_group + 1 : MIN_SPACE) << left << student.getGroup()
		<< setw(max_size_av_mark > MIN_SPACE ? max_size_av_mark + 1 : MIN_SPACE) << left << student.getAvgMark()
		<< setw(max_size_ed_form > MIN_SPACE ? max_size_ed_form + 1 : MIN_SPACE) << left << student.getEdFormWstr()
		<< setw(max_size_mail > MIN_SPACE ? max_size_mail + 1 : MIN_SPACE) << left << student.getEmail()
		<< setw(max_size_phone > MIN_SPACE ? max_size_phone + 1 : MIN_SPACE) << left << student.getPhone()
		<< left << L"│" << endl;
	wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;

	return wcout;
}
