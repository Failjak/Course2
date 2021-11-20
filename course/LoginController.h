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
	std::wstring user_file = L"user.txt";
	std::wstring admin_file = L"admin.txt";

	wstring clear_input(wstring, int mode = 1);

public:
	bool chekAuth(T);
	vector<T> ReadFromFile(T);
};
