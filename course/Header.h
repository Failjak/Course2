#pragma once
#include <iostream>
#include <stdio.h>
#include <cstdlib> // char to wchar_t
#include <string>
#include <windows.h>
#include <wincon.h>
#include <codecvt>
#include <locale>
#include <vector>
#include <map>




#define CIN_FLUSH if (std::cin.fail()) {std::cin.clear(); std::cin.ignore();}

constexpr auto DB_PATH = "migrate/main.db";
constexpr auto HEADER_SPACE = 32;

inline void coutTitle(std::wstring title) {
	int title_table_widht = HEADER_SPACE - title.length();
	std::wcout << std::wstring(title_table_widht, L'─') << title 
		<< std::wstring(title_table_widht, L'─') << L"\n" << std::endl;
}