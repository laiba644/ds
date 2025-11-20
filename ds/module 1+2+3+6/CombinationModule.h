#pragma once
#ifndef COMBINATIONMODULE_H
#define COMBINATIONMODULE_H

#include <iostream>
#include <string>
using namespace std;

class CombinationModule {
private:
	string* students;
	int studentCount;
	int studentCapacity;

	long long factorial(int n);
	long long nCr(int n, int r);
	void resizeStudents();

public:
	CombinationModule();
	~CombinationModule();

	void addStudent(const string& name);
	void loadStudents();
	void displayStudents();

	void generateProjectGroups(int groupSize);


	void generateProjectGroupsIterative(int groupSize);

	void assignLabSessions(int studentsPerLab);
	void displayCombinationStats();

	int getStudentCount() const;
};

#endif
