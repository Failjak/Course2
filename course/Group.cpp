#include "Group.h"

bool operator==(const Group & f1, const Group & f2)
{
	return (f1.name == f2.name);
}

Group::Group(const Group &tmp)
{
	name = tmp.name;
}