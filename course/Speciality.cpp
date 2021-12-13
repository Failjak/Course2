#include "Speciality.h"

Speciality::Speciality(const Speciality &tmp)
{
	id = tmp.id;
	abbrev = tmp.abbrev;
	name = tmp.name;
}


bool operator== (const Speciality &f1, const Speciality &f2)
{
	return (f1.abbrev == f2.abbrev &&
		f1.name == f2.name &&
		f1.id == f2.id);
}
