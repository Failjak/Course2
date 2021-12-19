#pragma once
#include <vector>
#include <string>

#include "AbstractHandler.h"
#include "Admin.h"
#include "User.h"

namespace AdminController{
	void main(Admin * admin);

	int menu();
	int user_menu();
	int stud_menu();
	int marks_menu();
	int stipend_out_menu();
	int stipend_menu();

	void pprintUser(std::vector<User*>, std::wstring title=L"");
	void pprinStudent(std::vector<Student*>, std::wstring title = L"");
	void pprinStipend(std::vector<Student*>, std::wstring title = L"");

	void StudentRating(Admin * s = new Admin());

	void UserManageController(Admin * admin);
	void StudentManageController(Admin * admin);
	void MarksManage(Admin * admin);
	void StipendManage(Admin * admin);
	void StipendOutput(Admin * admin);
	void EditManage(Admin * admin);
	void ManageData(Admin * admin);
	void FilterManage(Admin * admin, vector<User*> users);
	void SearchManage(Admin * admin, vector<User*> users);
};