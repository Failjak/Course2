#include "People.h"

using namespace std;

std::wstring People::strPPrint(std::wstring word)
{
	if (word.length() > 0)
	{
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}
		word[0] = toupper(word[0]);
	}

	return word;
}

void People::setName(std::wstring name)
{
	this->name = strPPrint(name);
}

void People::setSurname(std::wstring surname)
{
	this->surname = strPPrint(surname);
}

void People::setPatronomic(std::wstring patr)
{
	this->patronomic = strPPrint(patr);
}

std::wstring People::getFullName()
{
	return surname + L" " + name + L" " + patronomic;
}

std::wostream & operator<<(std::wostream & s, People *p)
{
	s << p->getFullName() << endl;
	return s;
}
