#include <Windows.h>

#include "UserController.h"
#include "AdminController.h"
#include "Header.h"
#include "DataBase.h"

namespace UserController
{

	void main(User * user)
	{
		DataBase db;
		user->setStudentId(db.getStudentIdByUser(user));
		user->setStudent();

		while (true)
		{
			switch (menu())
			{
			case 1:
			{
				system("cls");
				PersonalInfo(user);
				break;
			}

			case 2:
			{
				system("cls");
				ShowMarks(user);
				break;
			}
			case 3:
			{
				system("cls");
				StipendManage(user);
				break;
			}
			case 4:
			{
				system("cls");
				AdminController::StudentRating();
				break;
			}
			case 0:
				return;

			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
			system("cls");
		}
	}

	int menu()
	{
		coutTitle(L"Меню Студента");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Персональная информация." << endl;
		wcout << L"2) - Просмотр оценок." << endl;
		wcout << L"3) - Стипендия." << endl;
		wcout << L"4) - Рейтинг студентов" << endl;
		wcout << L"0) - Назад." << endl;
		wcout << L" Ваш выбор: ";

		while (flag)
		{
			rewind(stdin);
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"4") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	int personal_menu()
	{
		coutTitle(L"Персональная информация");

		bool flag = true;
		wstring choice;

		wcout << L"1) - Просмотр." << endl;
		wcout << L"2) - Редактирование." << endl;
		wcout << L"0) - Назад." << endl;
		wcout << L" Ваш выбор: ";

		while (flag)
		{
			getline(wcin, choice);
			if (choice >= L"0" && choice <= L"2") flag = false;
			else {
				wcout << L"Неверный выбор, попробуйте еще разок. " << endl;
				choice = L"";
			}
		}

		return stoi(choice);
	}

	void PersonalInfo(User * user)
	{
		while (true)
		{
			switch (personal_menu())
			{
			case 1:
			{
				system("cls");

				wcout << *user << endl;

				system("pause");
				system("cls");
				break;
			}
			case 2:
			{
				system("cls");

				auto res = Editing(user);

				if (res == 1)
					wcout << L"Редактирование выполнено успешно." << endl;
				else if (!res)
					wcout << L"Ошибка добавления данных." << endl;
				else if (res == -1)
					wcout << L"Выход." << endl;

				system("pause");
				system("cls");
				break;
			}
			case 0:
				return;

			default:
				wcout << L"Неверный выбор." << endl;
				break;
			}
			system("cls");
		}
	}

	void ShowMarks(User * user)
	{
		system("cls");

		pprintMark(user, L"Мои успехи");

		system("pause");
		system("cls");
	}

	void StipendManage(User * user)
	{
		system("cls");

		pprintStipend(user, L"Стипендия");

		system("pause");
		system("cls");
	}

	int Editing(User * user)
	{
		DataBase db;
		vector<wstring> columns = {
			L"Логин",
			L"Пароль",
		};

		coutTitle(L"Редактирование пользователя");
		wcout << *user << endl;

		wcout << L"Выберете поле для редактирования." << endl;

		int choice = AbstractHandler::choice_column(columns);

		if (choice == 1)
		{
			system("cls");

			wstring new_login;

			coutTitle(L"Изменение логина");
			wcout << L"Введите новый логин" << endl;

			wcin >> new_login;
			user->setLogin(new_login);

			if (db.DelNoteByStydentId(user->getStudentId(), *user) == 1
				and db.AddNoteUser(user) == 1
				and db.AddNoteStudent(user->getStudent()) == 1
				and db.AddNoteStudentGroup(user->getStudent()) == 1)
			{
				return 1;
			}
			else { return 0; }
		}
		else if (choice == 2)
		{
			system("cls");

			wstring new_pass;

			coutTitle(L"Изменение пароля");
			wcout << L"Введите новый пароль" << endl;

			wcin >> new_pass;
			user->setPassword(new_pass, 1);

			if (db.DelNoteByStydentId(user->getStudentId(), *user) == 1
				and db.AddNoteUser(user) == 1
				and db.AddNoteStudent(user->getStudent()) == 1
				and db.AddNoteStudentGroup(user->getStudent()) == 1)
			{
				return 1;
			}
			else { return 0; }
		}


		return -1;
	}

	void pprintMark(User * user, wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		map<int, map<wstring, int>> all_marks = user->getStudent()->getMarks();
		vector<wstring> subjs;

		vector<int> max_sizes_subjs;
		wstring title_term = L"Семестр";

		for (auto it = all_marks.cbegin(); it != all_marks.cend(); ++it)
		{
			for (auto n_it = (*it).second.cbegin(); n_it != (*it).second.cend(); ++n_it)
			{
				max_sizes_subjs.push_back(DB_SUBJS.count((*n_it).first) ? DB_SUBJS.at((*n_it).first).length() : 0);
				subjs.push_back((*n_it).first);
			}
			break;
		}

		int max_size_FN = user->getStudent()->getFullName().length();
		int max_size_term = title_term.length();
		int table_width = space_subjects + (
			(max_size_term > MIN_SPACE ? MIN_SPACE : max_size_term + 1));
		for (int i = 0; i < max_sizes_subjs.size(); i++)
			table_width += max_sizes_subjs.at(i);

		if (title.length())
		{
			int title_table_widht = (table_width - title.length()) / 2;
			wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
		}

		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";

		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << wstring((table_width - user->getStudent()->getFullName().length()) / 2, L' ')
			<< left << user->getStudent()->getFullName()
			<< wstring((table_width - user->getStudent()->getFullName().length()) / 2, L' ')
			<< left << L"│" << endl;
		wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;

		wcout << left << L"│";
		SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY);
		wcout << setw(max_size_term > MIN_SPACE ? MIN_SPACE : max_size_term + 1) << left << title_term;
		for (int i = 0; i < subjs.size(); i++) // перечисление предметов
		{
			wcout << setw(max_sizes_subjs.at(i) > MIN_SPACE ? MIN_SPACE : max_sizes_subjs.at(i) + 1) << left << DB_SUBJS.at(subjs.at(i));
		}

		SetConsoleTextAttribute(hCon, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		wcout << left << L"│" << endl;

		for (auto it = all_marks.cbegin(); it != all_marks.cend(); ++it)
		{
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;
			wcout << L"│" << setw(max_size_term > MIN_SPACE ? MIN_SPACE : max_size_term) << left << (*it).first;
			int i = 0;
			for (auto n_it = (*it).second.cbegin(); n_it != (*it).second.cend(); ++n_it, i++)
			{
				wcout
					<< setw(max_sizes_subjs.at(i))
					<< left << (*n_it).second;
			}
			wcout << left << L"│" << endl;
		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

	void pprintStipend(User * user, wstring title)
	{
		int space_subjects = 5;
		int MIN_SPACE = 14;
		HANDLE hCon;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);

		wstring title_term = L"Семестр", title_sitpend = L"Стипендия";

		int max_size_FN = user->getStudent()->getFullName().length();
		int max_size_term = title_term.length();
		int max_size_stipend = title_sitpend.length();
		int table_width = space_subjects;
		table_width += max_size_term + max_size_stipend > max_size_FN ? max_size_term + max_size_stipend : max_size_FN;

		if (title.length())
		{
			int title_table_widht = (table_width - title.length()) / 2;
			wcout << wstring(title_table_widht, L'─') << title << wstring(title_table_widht, L'─') << endl;
		}

		wcout << L"┌" << wstring(table_width, L'─') << L"┐" << endl;
		wcout << L"│";

		wcout << wstring((table_width - max_size_FN) / 2, L' ')
			<< left << user->getStudent()->getFullName()
			<< wstring((table_width - max_size_FN) / 2 + 1, L' ')
			<< left << L"│" << endl;
		wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl;

		wcout << left << L"│";
		wcout << setw(max_size_term) << left << L"Семестр"
			<< wstring((table_width - max_size_stipend - max_size_term) / 2, L' ');
		wcout << setw(max_size_stipend) << left << L"Стипендия"
			<< wstring((table_width - max_size_stipend - max_size_term) / 2, L' ');

		wcout << left << L"│" << endl;

		vector<pair<int, float>> stipends = user->getStudent()->getStipend();

		for (auto it = stipends.cbegin(); it != stipends.cend(); ++it) {
			wcout << L"├" << wstring(table_width, L'─') << L"┤" << endl << L"│";

			wcout << setw(max_size_term) << (*it).first
				<< wstring((table_width - max_size_stipend - max_size_term) / 2, L' ')
				<< setw(max_size_stipend) << left << (*it).second
				<< wstring((table_width - max_size_stipend - max_size_term) / 2, L' ')
				<< left << L"│" << endl;

		}
		wcout << L"└" << wstring(table_width, L'─') << L"┘" << endl;
	}

}