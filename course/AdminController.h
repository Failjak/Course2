#pragma once
#include <vector>
#include <string>

#include "Admin.h"

class AdminController {
public:
	static void main(Admin * admin);

	static int menu();
	static int user_menu();

	static void pprint(std::vector<std::vector<std::wstring>>, std::wstring title=L"");
	
	static void UserManageController(Admin * admin);
};