#pragma once
#include <vector>
#include <string>

class Encrypt {
	/*The Vernam cipher*/
private:
	static std::vector<int> key;

public:
	static std::wstring encrypt(std::wstring text);
	static std::wstring decrypt(std::wstring text);
};
