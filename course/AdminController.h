#pragma once
#include <vector>
#include <string>

#include "AbstractHandler.h"
#include "Admin.h"
#include "User.h"

class AdminController{
public:
	static void main(Admin * admin);

	static int menu();
	static int user_menu();
	static int stud_menu();
	static int marks_menu();
	static int stipend_menu();

	static void pprintUser(std::vector<User*>, std::wstring title=L"");
	static void pprinStudent(std::vector<Student*>, std::wstring title = L"");
	static void pprinStipend(std::vector<Student*>, std::wstring title = L"");
	
	static void UserManageController(Admin * admin);
	static void StudentManageController(Admin * admin);
	static void MarksManage(Admin * admin);
	static void StipendManage(Admin * admin);
	static void EditManage(Admin * admin);
};