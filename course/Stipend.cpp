#include "Stipend.h"

Stipend::Stipend(const Stipend &tmp)
{
	this->id = tmp.id;
	this->name = tmp.name;
	this->ratio = tmp.ratio;
	this->term = tmp.term;
}
