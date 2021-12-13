#pragma once
#include <string>

class Student;

class Faculty {
protected:
	int id;
	std::wstring abbrev;
	std::wstring name;

public:

	Faculty() {}
	Faculty(std::wstring abbrev) : abbrev(abbrev) {}
	Faculty(int id, std::wstring abbrev, std::wstring name) : id(id), abbrev(abbrev), name(name) {}
	Faculty(const Faculty &);

	void setId(int id) { this->id = id; }
	void setAbbrev(std::wstring abbrev) { this->abbrev = abbrev; }
	void setName(std::wstring name) { this->name = name; }

	std::wstring getAbbrev() { return abbrev; }
	std::wstring getName() { return name; }
	int getId() { return id; }

	friend bool operator== (const Faculty &f1, const Faculty &f2);

	friend class Student;
};