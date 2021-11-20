#pragma once

#include <string>


class People {
private:
	std::string name;
	std::string surname;
	std::string patronomic;

	std::string strPPrint(std::string);

public:
	People(std::string name, std::string surname, std::string patr) : name(strPPrint(name)), surname(strPPrint(surname)), patronomic(strPPrint(patr)) { ; }

	void setName(std::string name);
	void setSurname(std::string surname);
	void setPatronomic(std::string patr);

	std::string getName() { return name; }
	std::string getSurname() { return surname; }
	std::string getPatronomic() { return patronomic; }
	std::string getFullName();

};