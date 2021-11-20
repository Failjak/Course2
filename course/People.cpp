#include "People.h"

std::string People::strPPrint(std::string word)
{
	if (word.length() > 0)
	{
		for (int i = 0; i < word.length(); i++) {
			word[i] = islower(word[i]);
		}
		word[0] = toupper(word[0]);
	}
	return word;
}

void People::setName(std::string name)
{
	this->name = strPPrint(name);
}

void People::setSurname(std::string surname)
{
	this->surname = strPPrint(surname);
}

void People::setPatronomic(std::string patr)
{
	this->patronomic = strPPrint(patr);
}

std::string People::getFullName()
{
	return surname + " " + name + " " + patronomic;
}
