#include <conio.h>
#include <ctime>
#include <set>
#include <sstream>

#include "Admin.h"
#include "Header.h"

using namespace std;

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
		wcout << L"Отметки за все семестры занесены." << endl;
	}

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
			if (stoi(num + (wchar_t)ch) > 0 and stoi(num + (wchar_t)ch) <= course * 2)
			{
				wcout << (wchar_t)ch;
				num += (wchar_t)ch;
				if (!db.existMarks(student_id, stoi(num))) { break; }
			}
		}
	} while (true);
	marks.push_back(stoi(num));

	wcout << L"\nПересдачи(1-'да', 0-'нет'): ";
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

	wcout << L"\nВведите оценки по предметам:" << endl;
	for (int i = 2; i < subjs.size(); i++) // skip term and retake
	{
		num = L"";
		wcout << DB_SUBJS.at(subjs.at(i)) << L": ";

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

int Admin::getGroupExample(int group)
{
	if (to_string(group).length() == 5)
	{
		// 73601
		return (group / 100) % 100;
	}
	else if (to_string(group).length() == 6)
	{
		return (group / 100) % 1000;
	}
}

int Admin::EnterEdForm()
{
	coutTitle(L"Выбор формы обучения");

	wstring new_value;
	wchar_t ch;

	wcout << L"1) - Платное обучение." << endl;
	wcout << L"2) - Бюджетное обучение." << endl;
	while (true)
	{
		new_value = L"";
		ch = _getch();
		if (ch == 13 and new_value.length() > 0) { break; }
		if (ch == 32) { continue; }
		if (ch == 8 and new_value.length() > 0)
		{
			wcout << (wchar_t)8 << ' ' << wchar_t(8);
			new_value.erase(new_value.length() - 1, new_value.length());
		}
		else if (ch == 49 or ch == 50)
		{
			wcout << (wchar_t)ch;
			new_value += (wchar_t)ch;
			return stoi(new_value) - 1;
		}
	}
	
	wcout << endl;

	return -1;
}

vector<Student*> Admin::getStudents(wstring student_id)
{
	/*
		schema marks: student_id: {term, retake, subjs ...}
		get: student_id, условие, по которому надо выбирать студентов
		return: vector<student *> с заполненными полями (вычислена стипендия, заполнены имеющиеся отметки)
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
			//wcout << L"Такого студента не существует." << endl;
			return {};
		}
		students.push_back(db.getStudentById(student_id));
	}
	else
		students = db.getStudents();

	groups = db.getGroup2V();

	for (int i = 0; i < students.size(); i++)
	{
		wstring student_id = students.at(i)->getStudentId();

		marks = db.getMarks2VById(student_id);// получаю вектор с набором семестров и отметок за него
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

vector<User*> Admin::getUsers()
{
	DataBase db;
	vector<User *> users = db.getObj2V(User());

	for (int i = 0; i < users.size(); i++)
		users.at(i)->setStudent(db.getStudentById(users.at(i)->getStudentId()));

	return users;
}

vector<User*> Admin::getFullUser()
{
	DataBase db;
	vector<User *> users = db.getObj2V(User());
	wstring student_id;

	for (int i = 0; i < users.size(); i++)
	{
		student_id = users.at(i)->getStudentId();
		auto students = getStudents(student_id);
		if(!students.empty())
			users[i]->setStudent(students.front());
	}

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
	DataBase db;
	if (db.DelNoteByStydentId(s->getStudentId(), User()) == 1)
	{
		return 1;
	}

	return 0;
}

int Admin::EditUser(User * u)
{

	Student * s = u->getStudent();
	DataBase db;

	system("cls");
	coutTitle(L"Редактирование пользователя");

	wcout << *u << endl;
	wcout << L"Выберете поле для редактирования." << endl;
	
	vector<wstring> columns = {
		L"Логин", // 1
		L"Пароль",
		L"ФИО", // 3
		L"Факультет", // 4
		L"Специальность",
		L"Группа",
		L"Форма обучения", // 7
		L"Почта",
		L"Телефон",
	};

	int choice = AbstractHandler::choice_column(columns);

	wstring new_value;
	if (choice == 1)
	{
		system("cls");

		wstring new_login;

		coutTitle(L"Изменение логина");
		wcout << L"Введите новый логин" << endl;

		wcin >> new_login;

		u->setLogin(new_login);
		db.DelNoteByStydentId(u->getStudentId(), *u);
		db.AddNoteUser(u);
		db.AddNoteStudent(u->getStudent());
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 2)
	{
		system("cls");

		wstring new_pass;

		coutTitle(L"Изменение пароля");
		wcout << L"Введите новый пароль" << endl;

		wcin >> new_pass;

		u->setPassword(new_pass, 1);
		db.DelNoteByStydentId(u->getStudentId(), *u);
		db.AddNoteUser(u);
		db.AddNoteStudent(u->getStudent());
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 3) // Изменение ФИО
	{
		system("cls");  pair<wstring, wstring> new_fio = EnterFIO();
		if (new_fio.first == L"Фамилия"){
			s->setSurname(new_fio.second);
		}
		else if (new_fio.first == L"Имя"){
			s->setName(new_fio.second);
		}
		else if (new_fio.first == L"Отчество"){
			s->setPatronomic(new_fio.second);
		}

		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 4) // Факультет
	{
		system("cls");  wstring new_fac = EnterFaculty();

		if (new_fac == s->getFaculty()) 
			return -1;

		wcout << L"Так как Вы изменили Факультет, треубуется изменить Специальность и Группу." << endl;
		system("pause");

		system("cls");  wstring new_spec = EnterSpec(new_fac); 
		system("cls");  wstring new_group = EnterGroup(new_fac, new_spec);
		
		if (new_group == L"-1") { return -1; }

		s->setFaculty(new_fac);
		s->setSpec(new_spec);
		s->setGroup(new_group);

		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		/*wstring update_group_str = L"faculty = '" + new_fac + L", spec = '" + new_spec + L"' ,group_number = '" + new_group + L"'";
		db.updateGroup(u->getStudentId(), update_group_str);*/

		return true;
	}
	else if (choice == 5) // Спец
	{
		system("cls");  wstring new_spec = EnterSpec(s->getFaculty());
		system("cls");  wstring new_group = EnterGroup(s->getFaculty(), new_spec);

		if (new_group == L"-1" or new_spec == s->getSpec()) { return -1; }

		s->setSpec(new_spec);
		s->setGroup(new_group);

		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		/*wstring update_str = L"spec = '" + s->getSpec() + L"', group_number = '" + s->getGroup() + L"'";
		if (!db.updateGroup(u->getStudentId(), update_str)) { return false; }*/

		return true;
	}
	else if (choice == 6) //группа
	{
		system("cls");  wstring new_group = EnterGroup(s->getFaculty(), s->getSpec());

		if (new_group == L"-1" or new_group == s->getGroup()) { return -1; }

		s->setGroup(new_group);
		/*wstring update_str = L"group_number = '" + new_group + L"'";
		if (!db.updateGroup(u->getStudentId(), update_str)) { return false; }*/

		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 7) // ed form
	{
		int new_value = EnterEdForm();
		if (new_value == -1) { return false; }
		s->setEdForm(new_value);

		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 8)
	{
		system("cls");

		wstring new_mail;

		coutTitle(L"Изменение эл. почты");
		wcout << L"Введите новую почту" << endl;

		wcin >> new_mail;

		s->setEmail(new_mail);
		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		return true;
	}
	else if (choice == 9)
	{
		system("cls");

		wstring new_phone;

		coutTitle(L"Изменение номера телефона");
		wcout << L"Введите новый номер телефон" << endl;

		wcin >> new_phone;

		s->setPhone(new_phone);
		db.DelNoteByStydentId(u->getStudentId(), *s);
		db.AddNoteStudent(s);
		db.AddNoteStudentGroup(s);

		return true;
	}
	return 0;
}

int Admin::AddStudent()
{
	/*hot 
		return: 1 - no exeption;
				0 - faild insert.
	*/

	DataBase db;
	wstring last_name, patr, first_name, student_id, email, phone;
	wstring group, faculty, spec;
	int ed_form;

	coutTitle(L"Добавление пользователя");

	wcout << L"Введите ID студента: ";
	wcin >> student_id;
	wcout << L"Введите имя: ";
	wcin >> first_name;
	wcout << L"Введите фамилию: ";
	wcin >> last_name;
	wcout << L"Введите отчество: ";
	wcin >> patr;

	faculty = EnterFaculty();
	spec = EnterSpec(faculty);
	group = EnterGroup(faculty, spec);
	ed_form = EnterEdForm();
	wcout << L"Введите email: ";
	wcin >> email;
	wcout << L"Введите телефон: ";
	wcin >> phone;

	Student student(student_id, first_name, last_name, patr, group, faculty, spec, email, phone, L"");
	student.setEdForm(ed_form);

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
	DataBase db;
	if (db.DelNoteByStydentId(s->getStudentId(), Student()) == 1)
	{
		return 1;
	}

	return 0;
}

pair<wstring, wstring> Admin::EnterFIO()
{
	/*
		return: {column: new_value}	
	*/
	coutTitle(L"Редактирование ФИО");

	vector<wstring> columns = { L"Фамилия", L"Имя", L"Отчество" };
	wcout << L"Какое именно поле надо изменть" << endl;

	int choice = AbstractHandler::choice_column(columns);

	wstring new_value;
	wcout << L"Введите новое значение для '" << columns.at(choice - 1) << "': ";
	wcin >> new_value;

	return { columns.at(choice - 1), new_value };
}

wstring Admin::EnterFaculty()
{
	coutTitle(L"Выбор Факультета");

	DataBase db;
	map<int, pair<wstring, wstring>> faculties = db.getFaculties();
	vector<int> fac_codes;

	bool flag = true;
	wstring choice;

	wcout << L"Выберете новый факультет:" << endl;
	int i = 0;
	int key;

	for (const auto& fac : faculties)
	{
		wcout << ++i << L") " << fac.second.first << endl;
		fac_codes.push_back(fac.first);
	}

	wcout << L" Ваш выбор: ";
	while (flag)
	{
		rewind(stdin);
		getline(wcin, choice);
		if (choice >= L"1" && choice <= L"9") {
			try
			{
				key = fac_codes.at(stoi(choice) - 1);
				flag = false;
			}
			catch (std::out_of_range)
			{
				flag = true;
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}
		else {
			wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
			choice = L"";
		}
	}

	return faculties.at(key).first;
}

wstring Admin::EnterSpec(wstring faculty)
{
	wstring title = L"Выбор Специальности (" + faculty + L")";
	coutTitle(title);

	DataBase db;
	map<int, pair<wstring, wstring>> faculties = db.getFaculties();
	vector<int> spec_codes;
	int fac_code;

	for (const auto& fac : faculties)
		if (fac.second.first == faculty)
		{
			fac_code = fac.first;
			break;
		}

	map<int, pair<wstring, wstring>> specs = db.geSpecialities(fac_code);

	bool flag = true;
	wstring choice;
	int i = 0;
	int key;
	wcout << L"Выберете новую специальность:" << endl;

	for (const auto& spec : specs)
	{
		wcout << ++i << L") " << spec.second.first << endl;
		spec_codes.push_back(spec.first);
	}

	wostringstream fac_s;
	fac_s << faculties.size();
	wstring s = fac_s.str();

	wcout << L" Ваш выбор: ";
	while (flag)
	{
		rewind(stdin);
		getline(wcin, choice);
		if (choice >= L"1" && choice <= L"9") { 
			try
			{
				key = spec_codes.at(stoi(choice) - 1);
				flag = false;
			}
			catch (std::out_of_range)
			{
				flag = true;
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}
		else {
			wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
			choice = L"";
		}
	}

	
	return specs.at(key).first;
}

wstring Admin::EnterGroup(wstring faculty, wstring spec)
{
	wstring title = L"Ввод Группы (" + faculty + + L", " + spec + L")";
	coutTitle(title);

	DataBase db;
	map<int, pair<wstring, wstring>> faculties = db.getFaculties();
	int fac_code, spec_code;
	wstring group;

	for (const auto& fac : faculties)
		if (fac.second.first == faculty)
		{
			fac_code = fac.first;
			break;
		}
	map<int, pair<wstring, wstring>> specs = db.geSpecialities(fac_code);
	for (const auto& sp : specs)
		if (sp.second.first == spec)
		{
			spec_code = sp.first;
			break;
		}

	auto groups = db.getGroups(fac_code, spec_code);
	int ex_group = getGroupExample(groups.at(0));

	int flag = 1;
	wcout << L"Введите новый номер группы (×" + to_wstring(ex_group) + L"××): " << endl;

	try
	{
		do {

			if (!flag)
				wcout << L"Неверный формат. Попробуйте еще раз. (0 - выход)" << endl;

			wcin >> group;
			if (group == L"0") { return L"-1"; }

			flag = 0;
		} while (find(groups.begin(), groups.end(), stoi(group)) == groups.end());
	}
	catch (std::invalid_argument)
	{
		wcout << L"Ошибочное значение." << endl;
	}

	return group;
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
		wcout << L"Такого студента не существует." << endl;
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