#pragma once
#include <iostream>
#include <string>

/*----------------Class People--------------------*/
class People {
private:
	std::wstring name;
	std::wstring surname;
	std::wstring patronomic;

	std::wstring strPPrint(std::wstring);

public:
	People() { ; }
	People(std::wstring name, std::wstring surname, std::wstring patr) : name(strPPrint(name)), surname(strPPrint(surname)), patronomic(strPPrint(patr)) { ; }

	void setName(std::wstring name);
	void setSurname(std::wstring surname);
	void setPatronomic(std::wstring patr);

	std::wstring getName() { return name; }
	std::wstring getSurname() { return surname; }
	std::wstring getPatronomic() { return patronomic; }
	std::wstring getFullName();

	friend std::wostream &operator<<(std::wostream &s, People * p);
};