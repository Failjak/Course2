#pragma once
#include <string>

class Stipend
{
private:
	int id;
	std::wstring name;
	float ratio;
	int term;

public:
	Stipend(int id, std::wstring name, float ratio, int term) :
		id(id), name(name), ratio(ratio), term(term) {}
	Stipend() {}
	Stipend(const Stipend &);

	int getId() { return id; }
	std::wstring getName() { return name; }
	float getRatio() { return ratio; }
	int getTerm() { return term; }

	void setId(int id) { this->id = id; }
	void setName(std::wstring name) { this->name = name; }
	void setRatio(float ratio) { this->ratio = ratio; }
	void setTerm(int term) { this->term = term; }
};
