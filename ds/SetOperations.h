#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <iostream>
#include <string>
using namespace std;

class SetOperations {
public:
	struct Set {
		string name;
		string* elements;
		int size;
		int capacity;

		Set();
		Set(const string& setName);
		~Set();

		void addElement(const string& element);
		bool contains(const string& element) const;
		void display() const;
		void clear();
	};

private:
	Set** sets;
	int setCount;
	int setCapacity;

	void resizeSets();
	int findSetIndex(const string& setName) const;
	void removeElement(string* arr, int& size, int index);

public:
	SetOperations();
	~SetOperations();

	void createSet(const string& setName);
	void addElementToSet(const string& setName, const string& element);
	void displaySet(const string& setName) const;
	void displayAllSets() const;
	Set* getSet(const string& setName) const;

	Set* unionSets(const string& setA, const string& setB);
	Set* intersectionSets(const string& setA, const string& setB);
	Set* differenceSets(const string& setA, const string& setB);

	bool isSubset(const string& setA, const string& setB) const;
	bool isSuperset(const string& setA, const string& setB) const;
	bool isProperSubset(const string& setA, const string& setB) const;
	bool areDisjoint(const string& setA, const string& setB) const;
	bool areEqual(const string& setA, const string& setB) const;

	int cardinality(const string& setName) const;

	void generatePowerSet(const string& setName);
	void cartesianProduct(const string& setA, const string& setB);
	Set* complement(const string& setName, const string& universalSetName);

	void findStudentsInBothCourses(const string& course1, const string& course2);
	void findStudentsInEitherCourse(const string& course1, const string& course2);
	void findStudentsOnlyInOneCourse(const string& course1, const string& course2);
	void findCommonFaculties(const string& dept1, const string& dept2);

	void demonstrateSetOperations();
	void testUniversityScenario();
};

#endif