#pragma once
#include <string>

class Stipend
{
private:
	int id;
	std::wstring name;
	float ratio;

public:
	Stipend(int id, std::wstring name, float ratio) :
		id(id), name(name), ratio(ratio) {}
	Stipend() {}
	Stipend(const Stipend &);

	int getId() { return id; }
	std::wstring getName() { return name; }
	float getRatio() { return ratio; }

	void setId(int id) { this->id = id; }
	void setName(std::wstring name) { this->name = name; }
	void setRatio(float ratio) { this->ratio = ratio; }
};
