#pragma once

#include "User.h"

namespace UserController
{
	void main(User * user);
	
	int menu();
	int personal_menu();

	void PersonalInfo(User *);
	void ShowMarks(User *);
	void StipendManage(User *);
	int Editing(User *);

	void pprintMark(User *, wstring);
	void pprintStipend(User *, wstring);
}