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

namespace Stipend
{
	constexpr auto BASE_STIPEND = 96.37;
	constexpr auto MIN_LIVING_STANDART = 321.22;

	const std::map<std::wstring, std::pair<float, float>> stipend_condition = {
		{L"zero", {0, 4.9}},
		{L"base", {5.0, 5.9}},
		{L"min", {6.0, 7.9} },
		{L"middle", {8.0, 8.9} },
		{L"max", {9.0, 10.9} }
	};

	const std::map<std::wstring, float> stipend_rate = {
		{L"zero", 0},
		{L"base", 1},
		{L"min", 1.2 },
		{L"middle", 1.4 },
		{L"max", 1.6} 
	};

	const std::map<std::wstring, float> additional_stipend_rate = {
		{L"personal", 0.7},
		{L"univcouncil", 0.61 },
	};
}


const std::map<std::wstring, std::wstring> DBfield_subj = {
	{L"Math", L"Матем"},
	{L"OOP", L"ООП"},
	{L"Philosophy", L"Философия"},
	{L"CN", L"КС"},
	{L"Economic", L"Экономика"}
};