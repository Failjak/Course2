#pragma once

#include "User.h"

class UserController {
public:
	static void main(User * user);
	
	static int menu();
	static int personal_menu();
	static int choice_column(vector<wstring>);

	static void PersonalInfo(User *);
	static void ShowMarks(User *);
	static void StipendManage(User *);
	static int Editing(User *);

	static void pprintMark(User *, wstring);
	static void pprintStipend(User *, wstring);
};