#pragma once

#include "Header.h"
#include "Student.h"
#include "DataBase.h"

namespace AbstractHandler
{
		/*─────Comparatros─────*/
	bool compByAvgMark(Student * s1, Student * s2);
		/*─────Comparatros─────*/

	int choice_column(vector<wstring>);

	void StudentRating(vector<Student *> students, vector<wstring> fac_spec_group);
	void pprintStudentRating(vector<Student *> students);
}
