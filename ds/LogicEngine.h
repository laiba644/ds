#ifndef LOGICENGINE_H
#define LOGICENGINE_H
#include <iostream>
#include <string>
using namespace std;

class CourseScheduling;

class LogicEngine {
public:
	struct Rule {
		string ruleType;
		string condition;
		string conclusion;
		bool isActive;

		Rule();
		Rule(const string& type, const string& cond, const string& concl);
	};

	struct Fact {
		string factType;
		string subject;
		string predicate;
		string object;
		bool isTrue;

		Fact();
		Fact(const string& type, const string& subj, const string& pred, const string& obj, bool truth = true);
	};

public:
	CourseScheduling* courseSystem;

	Rule** rules;
	int ruleCount;
	int ruleCapacity;

	Fact** facts;
	int factCount;
	int factCapacity;

	string** knowledgeBase;
	int kbCount;
	int kbCapacity;

	string* predicateNames;
	int predicateCount;
	int predicateCapacity;

	void resizeRules();
	void resizeFacts();
	void resizeKB();

	bool matchesPattern(const string& pattern, const string& fact);
	bool evaluateCondition(const string& condition);
	string substituteVariables(const string& template_str, const string& var, const string& value);

	bool modusPonens(const Rule& rule);
	bool modusTollens(const Rule& rule);
	void forwardChaining();
	bool backwardChaining(const string& goal);

public:
	LogicEngine(CourseScheduling* ptr);
	~LogicEngine();

	void addRule(const string& type, const string& condition, const string& conclusion);
	void displayRules();
	void enableRule(int index);
	void disableRule(int index);

	void addFact(const string& type, const string& subject, const string& predicate,
		const string& object, bool truth = true);
	void displayFacts();
	bool checkFact(const string& type, const string& subject, const string& predicate,
		const string& object);

	void inferNewFacts();
	void verifyAllRules();
	bool queryKnowledgeBase(const string& query);

	void detectCourseConflicts();
	void detectFacultyConflicts();
	void detectLabConflicts();

	void loadDefaultRules();
	void addPrerequisiteRule(const string& course, const string& prerequisite);
	void addFacultyAssignmentRule(const string& faculty, const string& course, const string& lab);
	void addTimeConflictRule(const string& course1, const string& course2);

	bool verifyStudentEnrollment(const string& studentID, const string& courseCode);
	bool verifyFacultyAssignment(const string& facultyID, const string& courseCode);
	bool verifyLabAllocation(const string& courseCode, const string& labID);

	bool isTautology(const string& proposition);

	void addPredicate(const string& name, const string& var1, const string& var2 = "");
	void displayPredicates();
	bool checkPredicate(const string& predicateName, const string& arg1, const string& arg2 = "");

	bool universalQuantifier(const string& predicateName, string domain[], int size);
	bool existentialQuantifier(const string& predicateName, string domain[], int size);
	void demoTautologyAndPredicates();

	void generateInferenceReport();
	void displayKnowledgeBase();
};

#endif