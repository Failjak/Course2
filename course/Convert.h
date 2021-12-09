#pragma once
#include "Header.h"

using namespace std;

namespace Convert
{
	const std::wstring S2WS(const std::string &s);
	std::string WS2S(const std::wstring& wstr);
	vector<vector<wstring>> VVS2VVWS(const vector<vector<string>> vvs);
}