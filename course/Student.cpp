#include "Student.h"

void Student::setMarks(vector<wstring> tmp)
{
	//stoi(ws);
	for (int i = 0; i < tmp.size(); i++)
	{
		wcout << tmp.at(i) << endl;
	}
}
