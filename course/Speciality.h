#pragma once
#include <string>

class Speciality
{
private:
	int id;
	std::wstring abbrev;
	std::wstring name;

public:
	Speciality() { ; }
	Speciality(std::wstring abbrev) : abbrev(abbrev) { ; }
	Speciality(int id, std::wstring abbrev, std::wstring name) : id(id), abbrev(abbrev), name(name) { ; }
	Speciality(const Speciality &);

	void setId(int id) { this->id = id; }
	void setAbbrev(std::wstring abbrev) { this->abbrev = abbrev; }
	void setName(std::wstring name) { this->name = name; }

	std::wstring getAbbrev() { return abbrev; }
	std::wstring getName() { return name; }
	int getId() { return id; }

	friend bool operator== (const Speciality &s1, const Speciality &s2);

	friend class Speciality;
};