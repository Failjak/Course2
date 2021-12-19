#pragma once

#include "Header.h"
#include "Stipend.h"
#include "Student.h"
#include "DataBase.h"

namespace AbstractHandler
{
	/*─────Comparatros─────*/
	bool compByAvgMark(Student * s1, Student * s2);
	bool compBySurname(User * u1, User * u2);
	bool compByName(User * u1, User * u2);
	bool UcompByFIO(User * u1, User * u2);
	bool ScompByFIO(Student * s1, Student * s2);
	/*─────Comparatros─────*/

	int choice_column(vector<wstring>);
	int choice_column(int columns_count);

	vector<User *> searchSurname(vector<User *> users, wstring surname);
	vector<User *> searchName(vector<User *> users, wstring name);
	vector<User *> searchLogin(vector<User *> users, wstring name);
	vector<User *> searchMail(vector<User *> users, wstring name);
	vector<User *> searchPhone(vector<User *> users, wstring name);

	vector<User *> filterByEdForm(vector<User *> users, int form);
	vector<User *> filterByFSG(vector<User *>, wstring fac);
	vector<User *> filterByFSG(vector<User *>, wstring fac, wstring spec);
	vector<User *> filterByFSG(vector<User *>, wstring fac, wstring spec, wstring group);

	void StudentRating(vector<Student *> students, vector<wstring> fac_spec_group);
	void pprintStudentRating(vector<Student *> students);
	void pprintAdditStipend(std::vector<Stipend*>, std::wstring title = L"");

	wstring ppWstring(wstring word);
}