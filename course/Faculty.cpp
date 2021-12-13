#include "Faculty.h"

Faculty::Faculty(const Faculty &tmp)
{
	id = tmp.id;
	abbrev = tmp.abbrev;
	name = tmp.name;
}

bool operator== (const Faculty &f1, const Faculty &f2)
{
	return (f1.abbrev == f2.abbrev &&
		f1.name == f2.name &&
		f1.id == f2.id);
}
