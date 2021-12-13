#include <wctype.h>
#include <locale.h>

#include "People.h"

using namespace std;

wstring People::strPPrint(std::wstring word)
{
	if (word.length() > 0)
	{
		for (int i = 0; i < word.length(); i++) {
			word[i] = _towlower_l(word[i], _create_locale(LC_ALL, "Russian"));
		}
		word[0] = _towupper_l(word[0], _create_locale(LC_ALL, "Russian"));
	}

	return word;
}

std::wstring People::strPPrintL(std::wstring word)
{
	if (word.length() > 0)
		for (int i = 0; i < word.length(); i++)
			word[i] = _towlower_l(word[i], _create_locale(LC_ALL, "Russian"));

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
