#pragma once
#include <iostream>
#include <string>

/*----------------Class People--------------------*/
class People {
protected:
	std::wstring name;
	std::wstring surname;
	std::wstring patronomic;

	std::wstring strPPrint(std::wstring);
	std::wstring strPPrintL(std::wstring);

public:
	People() { ; }
	People(std::wstring name, std::wstring surname, std::wstring patr) : name(strPPrint(name)), surname(strPPrint(surname)), patronomic(strPPrint(patr)) { ; }
	People(const People & tmp) {
		name = tmp.name; surname = tmp.surname; patronomic = tmp.patronomic;
	}

	virtual void setName(std::wstring name);
	virtual void setSurname(std::wstring surname);
	virtual void setPatronomic(std::wstring patr);

	virtual std::wstring getName() { return name; }
	virtual std::wstring getNameL() { return strPPrintL(name); }
	virtual std::wstring getSurname() { return surname; }
	virtual std::wstring getPatronomic() { return patronomic; }
	virtual std::wstring getFullName();

	friend std::wostream &operator<<(std::wostream &s, People * p);

	virtual void printRole() = 0;
};