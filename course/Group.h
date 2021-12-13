#pragma once
#include <string>

class Group
{
private:
	std::wstring name;

public:

	Group() {}
	Group(std::wstring name) : name(name) {}
	Group(const Group &);

	void setName(std::wstring name) { this->name = name; }

	std::wstring getName() { return name; }

	friend bool operator== (const Group &f1, const Group &f2);

	friend class Student;
};