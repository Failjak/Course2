#pragma once
#include <vector>
#include <string>

#include "Admin.h"
#include "User.h"

class AdminController {
public:
	static void main(Admin * admin);

	static int menu();
	static int user_menu();
	static int stud_menu();

	static void pprint(std::vector<User*>, std::wstring title=L"");
	
	static void UserManageController(Admin * admin);
	static void StudentManageController(Admin * admin);
};