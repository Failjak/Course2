#pragma once 
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "User.h"
#include "Admin.h"

using namespace std;

template <class T>
class LoginController {
private:
	std::string user_file = "user.txt";
	std::string admin_file = "admin.txt";

	wstring clear_input(wstring, int mode = 1);

public:
	bool chekAuth(T);
	vector<T> ReadFromFile(T);
};
