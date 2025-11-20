#include "LogicEngine.h"
#include "CourseScheduling.h"
#include <sstream>

LogicEngine::Rule::Rule() {
	isActive = true;
}

LogicEngine::Rule::Rule(const string& type, const string& cond, const string& concl) {
	ruleType = type;
	condition = cond;
	conclusion = concl;
	isActive = true;
}

LogicEngine::Fact::Fact() {
	isTrue = true;
}

LogicEngine::Fact::Fact(const string& type, const string& subj, const string& pred,
	const string& obj, bool truth) {
	factType = type;
	subject = subj;
	predicate = pred;
	object = obj;
	isTrue = truth;
}

LogicEngine::LogicEngine(CourseScheduling* ptr) {
	courseSystem = ptr;

	ruleCount = 0;
	ruleCapacity = 20;
	rules = new Rule * [ruleCapacity];

	factCount = 0;
	factCapacity = 50;
	facts = new Fact * [factCapacity];

	kbCount = 0;
	kbCapacity = 100;
	knowledgeBase = new string * [kbCapacity];
	for (int i = 0; i < kbCapacity; i++) {
		knowledgeBase[i] = new string[3];
	}

	predicateCount = 0;
	predicateCapacity = 20;
	predicateNames = new string[predicateCapacity];
}

LogicEngine::~LogicEngine() {
	for (int i = 0; i < ruleCount; i++)
		delete rules[i];
	delete[] rules;

	for (int i = 0; i < factCount; i++)
		delete facts[i];
	delete[] facts;

	for (int i = 0; i < kbCapacity; i++)
		delete[] knowledgeBase[i];
	delete[] knowledgeBase;

	delete[] predicateNames;
}

void LogicEngine::resizeRules() {
	ruleCapacity *= 2;
	Rule** temp = new Rule * [ruleCapacity];
	for (int i = 0; i < ruleCount; i++)
		temp[i] = rules[i];
	delete[] rules;
	rules = temp;
}

void LogicEngine::resizeFacts() {
	factCapacity *= 2;
	Fact** temp = new Fact * [factCapacity];
	for (int i = 0; i < factCount; i++)
		temp[i] = facts[i];
	delete[] facts;
	facts = temp;
}

void LogicEngine::resizeKB() {
	int newCap = kbCapacity * 2;
	string** temp = new string * [newCap];
	for (int i = 0; i < newCap; i++) {
		temp[i] = new string[3];
		if (i < kbCapacity) {
			temp[i][0] = knowledgeBase[i][0];
			temp[i][1] = knowledgeBase[i][1];
			temp[i][2] = knowledgeBase[i][2];
		}
	}
	for (int i = 0; i < kbCapacity; i++)
		delete[] knowledgeBase[i];
	delete[] knowledgeBase;
	knowledgeBase = temp;
	kbCapacity = newCap;
}

void LogicEngine::addRule(const string& type, const string& condition, const string& conclusion) {
	if (ruleCount >= ruleCapacity)
		resizeRules();

	rules[ruleCount++] = new Rule(type, condition, conclusion);
	cout << "Rule added: IF " << condition << " THEN " << conclusion << "\n";
}

void LogicEngine::displayRules() {
	cout << "\n";
	cout << "LOGICAL RULES\n";
	cout << "\n";

	if (ruleCount == 0) {
		cout << "No rules defined.\n";
		return;
	}

	for (int i = 0; i < ruleCount; i++) {
		cout << "\nRule " << (i + 1) << " [" << rules[i]->ruleType << "]";
		cout << " [" << (rules[i]->isActive ? "ACTIVE" : "INACTIVE") << "]\n";
		cout << "  IF:   " << rules[i]->condition << "\n";
		cout << "  THEN: " << rules[i]->conclusion << "\n";
	}
}

void LogicEngine::enableRule(int index) {
	if (index >= 0 && index < ruleCount) {
		rules[index]->isActive = true;
		cout << "Rule " << (index + 1) << " enabled.\n";
	}
}

void LogicEngine::disableRule(int index) {
	if (index >= 0 && index < ruleCount) {
		rules[index]->isActive = false;
		cout << "Rule " << (index + 1) << " disabled.\n";
	}
}

void LogicEngine::addFact(const string& type, const string& subject,
	const string& predicate, const string& object, bool truth) {
	if (factCount >= factCapacity)
		resizeFacts();

	facts[factCount++] = new Fact(type, subject, predicate, object, truth);

	if (kbCount >= kbCapacity)
		resizeKB();

	knowledgeBase[kbCount][0] = subject;
	knowledgeBase[kbCount][1] = predicate;
	knowledgeBase[kbCount][2] = object;
	kbCount++;
}

void LogicEngine::displayFacts() {
	cout << "\n";
	cout << "KNOWN FACTS\n";
	cout << "\n";

	if (factCount == 0) {
		cout << "No facts in knowledge base.\n";
		return;
	}

	for (int i = 0; i < factCount; i++) {
		cout << (i + 1) << ". [" << facts[i]->factType << "] ";
		cout << facts[i]->subject << " " << facts[i]->predicate << " " << facts[i]->object;
		if (!facts[i]->isTrue)
			cout << " (FALSE)";
		cout << "\n";
	}
}

bool LogicEngine::checkFact(const string& type, const string& subject,
	const string& predicate, const string& object) {
	for (int i = 0; i < factCount; i++) {
		if (facts[i]->factType == type &&
			facts[i]->subject == subject &&
			facts[i]->predicate == predicate &&
			facts[i]->object == object &&
			facts[i]->isTrue) {
			return true;
		}
	}
	return false;
}

bool LogicEngine::matchesPattern(const string& pattern, const string& fact) {
	if (pattern == fact)
		return true;

	if (pattern.find("*") != string::npos) {
		return true;
	}

	return false;
}

bool LogicEngine::evaluateCondition(const string& condition) {
	stringstream ss(condition);
	string subject, predicate, object;
	ss >> subject >> predicate >> object;

	for (int i = 0; i < kbCount; i++) {
		if (knowledgeBase[i][0] == subject &&
			knowledgeBase[i][1] == predicate &&
			knowledgeBase[i][2] == object) {
			return true;
		}
	}

	return false;
}

bool LogicEngine::modusPonens(const Rule& rule) {
	if (!rule.isActive)
		return false;

	if (evaluateCondition(rule.condition)) {
		stringstream ss(rule.conclusion);
		string subject, predicate, object;
		ss >> subject >> predicate >> object;

		for (int i = 0; i < kbCount; i++) {
			if (knowledgeBase[i][0] == subject &&
				knowledgeBase[i][1] == predicate &&
				knowledgeBase[i][2] == object) {
				return false;
			}
		}

		if (kbCount >= kbCapacity)
			resizeKB();

		knowledgeBase[kbCount][0] = subject;
		knowledgeBase[kbCount][1] = predicate;
		knowledgeBase[kbCount][2] = object;
		kbCount++;

		cout << "Inferred: " << rule.conclusion << "\n";
		return true;
	}

	return false;
}

void LogicEngine::forwardChaining() {
	cout << "\n";
	cout << "FORWARD CHAINING INFERENCE\n";
	cout << "\n";

	bool newInference = true;
	int iterations = 0;

	while (newInference && iterations < 100) {
		newInference = false;
		iterations++;

		cout << "\nIteration " << iterations << ":\n";

		for (int i = 0; i < ruleCount; i++) {
			if (modusPonens(*rules[i])) {
				newInference = true;
			}
		}

		if (!newInference) {
			cout << "No new inferences in this iteration.\n";
		}
	}

	cout << "\nForward chaining completed after " << iterations << " iterations.\n";
}

void LogicEngine::inferNewFacts() {
	forwardChaining();
}

void LogicEngine::verifyAllRules() {
	cout << "\n";
	cout << "RULE VERIFICATION\n";
	cout << "\n";

	int satisfied = 0;
	int violated = 0;

	for (int i = 0; i < ruleCount; i++) {
		if (!rules[i]->isActive)
			continue;

		bool conditionMet = evaluateCondition(rules[i]->condition);
		bool conclusionMet = evaluateCondition(rules[i]->conclusion);

		cout << "\nRule " << (i + 1) << ": ";

		if (conditionMet && conclusionMet) {
			cout << "SATISFIED\n";
			satisfied++;
		}
		else if (conditionMet && !conclusionMet) {
			cout << "VIOLATED (condition true but conclusion false)\n";
			violated++;
		}
		else {
			cout << "NOT APPLICABLE (condition false)\n";
		}
	}

	cout << "\n";
	cout << "Satisfied: " << satisfied << " | Violated: " << violated << "\n";
}

void LogicEngine::detectCourseConflicts() {
	cout << "\n";
	cout << "COURSE CONFLICT DETECTION\n";
	cout << "\n";

	int conflicts = 0;

	for (int i = 0; i < factCount; i++) {
		if (facts[i]->factType == "STUDENT_ENROLLED") {
			string studentID = facts[i]->subject;
			string courseCode = facts[i]->object;

			CourseScheduling::Course* course = courseSystem->findCourse(courseCode);
			if (course) {
				for (int j = 0; j < course->prereqCount; j++) {
					string prereq = course->prerequisites[j];

					bool completed = false;
					for (int k = 0; k < factCount; k++) {
						if (facts[k]->factType == "STUDENT_COMPLETED" &&
							facts[k]->subject == studentID &&
							facts[k]->object == prereq) {
							completed = true;
							break;
						}
					}

					if (!completed) {
						cout << "CONFLICT: Student " << studentID
							<< " enrolled in " << courseCode
							<< " without completing " << prereq << "\n";
						conflicts++;
					}
				}
			}
		}
	}

	if (conflicts == 0) {
		cout << "No course conflicts detected.\n";
	}
	else {
		cout << "\nTotal conflicts: " << conflicts << "\n";
	}
}

void LogicEngine::detectFacultyConflicts() {
	cout << "\n";
	cout << "FACULTY CONFLICT DETECTION\n";
	cout << "\n";

	int conflicts = 0;

	for (int i = 0; i < factCount; i++) {
		if (facts[i]->factType == "FACULTY_TEACHES") {
			string faculty = facts[i]->subject;
			string course = facts[i]->object;

			for (int j = i + 1; j < factCount; j++) {
				if (facts[j]->factType == "FACULTY_TEACHES" &&
					facts[j]->object == course &&
					facts[j]->subject != faculty) {
					cout << "CONFLICT: Course " << course
						<< " assigned to multiple faculty: "
						<< faculty << " and " << facts[j]->subject << "\n";
					conflicts++;
				}
			}
		}
	}

	if (conflicts == 0) {
		cout << "No faculty conflicts detected.\n";
	}
	else {
		cout << "\nTotal conflicts: " << conflicts << "\n";
	}
}

void LogicEngine::detectLabConflicts() {
	cout << "\n";
	cout << "LAB CONFLICT DETECTION\n";
	cout << "\n";

	int conflicts = 0;

	for (int i = 0; i < factCount; i++) {
		if (facts[i]->factType == "LAB_ALLOCATED") {
			string course = facts[i]->subject;
			string lab = facts[i]->object;

			for (int j = i + 1; j < factCount; j++) {
				if (facts[j]->factType == "LAB_ALLOCATED" &&
					facts[j]->object == lab &&
					facts[j]->subject != course) {
					cout << "CONFLICT: Lab " << lab
						<< " allocated to multiple courses: "
						<< course << " and " << facts[j]->subject << "\n";
					conflicts++;
				}
			}
		}
	}

	if (conflicts == 0) {
		cout << "No lab conflicts detected.\n";
	}
	else {
		cout << "\nTotal conflicts: " << conflicts << "\n";
	}
}

void LogicEngine::loadDefaultRules() {
	cout << "\nLoading default logical rules...\n";

	addRule("PREREQUISITE",
		"STUDENT ENROLLED CS2001",
		"STUDENT MUST_COMPLETE CS1004");

	addRule("PREREQUISITE",
		"STUDENT ENROLLED CS2006",
		"STUDENT MUST_COMPLETE CS2001");

	addRule("FACULTY_ASSIGNMENT",
		"FACULTY_X TEACHES CS101",
		"CS101 REQUIRES LAB_A");

	addRule("FACULTY_ASSIGNMENT",
		"FACULTY_Y TEACHES CS201",
		"CS201 REQUIRES LAB_B");

	addRule("CAPACITY",
		"LAB_A HAS CAPACITY_20",
		"COURSE ENROLLMENT LIMITED_20");

	cout << "Default rules loaded.\n";
}

void LogicEngine::addPrerequisiteRule(const string& course, const string& prerequisite) {
	string condition = "STUDENT ENROLLED " + course;
	string conclusion = "STUDENT MUST_COMPLETE " + prerequisite;
	addRule("PREREQUISITE", condition, conclusion);
}

void LogicEngine::addFacultyAssignmentRule(const string& faculty, const string& course, const string& lab) {
	string condition = faculty + " TEACHES " + course;
	string conclusion = course + " REQUIRES " + lab;
	addRule("FACULTY_ASSIGNMENT", condition, conclusion);
}

bool LogicEngine::verifyStudentEnrollment(const string& studentID, const string& courseCode) {
	return checkFact("STUDENT_ENROLLED", studentID, "ENROLLED_IN", courseCode);
}

bool LogicEngine::verifyFacultyAssignment(const string& facultyID, const string& courseCode) {
	return checkFact("FACULTY_TEACHES", facultyID, "TEACHES", courseCode);
}

bool LogicEngine::verifyLabAllocation(const string& courseCode, const string& labID) {
	return checkFact("LAB_ALLOCATED", courseCode, "USES_LAB", labID);
}

void LogicEngine::generateInferenceReport() {
	cout << "\n";
	cout << "INFERENCE ENGINE REPORT\n";
	cout << "\n";

	cout << "\nStatistics:\n";
	cout << "  Rules defined:     " << ruleCount << "\n";
	cout << "  Facts in KB:       " << factCount << "\n";
	cout << "  Derived facts:     " << kbCount << "\n";

	cout << "\nRule Distribution:\n";
	int prereqRules = 0, facultyRules = 0, otherRules = 0;

	for (int i = 0; i < ruleCount; i++) {
		if (rules[i]->ruleType == "PREREQUISITE")
			prereqRules++;
		else if (rules[i]->ruleType == "FACULTY_ASSIGNMENT")
			facultyRules++;
		else
			otherRules++;
	}

	cout << "  Prerequisite rules:       " << prereqRules << "\n";
	cout << "  Faculty assignment rules: " << facultyRules << "\n";
	cout << "  Other rules:              " << otherRules << "\n";

	cout << "\n";
}

void LogicEngine::displayKnowledgeBase() {
	cout << "\n";
	cout << "KNOWLEDGE BASE\n";
	cout << "\n";

	if (kbCount == 0) {
		cout << "Knowledge base is empty.\n";
		return;
	}

	for (int i = 0; i < kbCount; i++) {
		cout << (i + 1) << ". "
			<< knowledgeBase[i][0] << " "
			<< knowledgeBase[i][1] << " "
			<< knowledgeBase[i][2] << "\n";
	}

	cout << "\nTotal entries: " << kbCount << "\n";
}

bool LogicEngine::isTautology(const string& proposition) {
	cout << "\n";
	cout << "TAUTOLOGY CHECKER\n";
	cout << "\n";
	cout << "Proposition: " << proposition << "\n";
	cout << "Method: Check all truth value combinations\n\n";

	string prop = proposition;

	bool hasA = (prop.find('A') != string::npos || prop.find('a') != string::npos);
	bool hasB = (prop.find('B') != string::npos || prop.find('b') != string::npos);

	int numVars = 0;
	if (hasA) numVars++;
	if (hasB) numVars++;

	if (numVars == 0) {
		cout << "No variables found.\n";
		return false;
	}

	int rows = 1;
	for (int i = 0; i < numVars; i++) rows *= 2;

	cout << "Variables: " << numVars << " (";
	if (hasA) cout << "A";
	if (hasA && hasB) cout << ", ";
	if (hasB) cout << "B";
	cout << ")\n";
	cout << "Total combinations to check: " << rows << "\n\n";

	bool isTaut = true;
	int falseCount = 0;

	for (int i = 0; i < rows; i++) {
		bool A = false, B = false;

		if (numVars == 1) {
			A = (i == 1);
		}
		else if (numVars == 2) {
			A = (i / 2 == 1);
			B = (i % 2 == 1);
		}

		bool result = false;

		if (prop == "A|!A" || prop == "a|!a") {
			result = A || !A;
		}
		else if (prop == "!(A&!A)" || prop == "!(a&!a)") {
			result = !(A && !A);
		}
		else if (prop == "A->A" || prop == "a->a") {
			result = !A || A;
		}
		else if (prop == "A&B" || prop == "a&b") {
			result = A && B;
		}
		else if (prop == "A|B" || prop == "a|b") {
			result = A || B;
		}
		else if (prop == "!A|B" || prop == "!a|b") {
			result = !A || B;
		}
		else if (prop == "A" || prop == "a") {
			result = A;
		}
		else {
			cout << "Unsupported proposition format.\n";
			cout << "Use: A|!A, !(A&!A), A&B, A|B, !A|B\n";
			return false;
		}

		cout << "Row " << (i + 1) << ": ";
		if (hasA) cout << "A=" << (A ? "T" : "F") << " ";
		if (hasB) cout << "B=" << (B ? "T" : "F") << " ";
		cout << "-> Result: " << (result ? "TRUE" : "FALSE");

		if (!result) {
			cout << " [X]";
			isTaut = false;
			falseCount++;
		}
		else {
			cout << " [OK]";
		}
		cout << "\n";
	}

	cout << "\n";
	cout << "RESULT: ";
	if (isTaut) {
		cout << "TAUTOLOGY\n";
		cout << "All " << rows << " combinations are TRUE.\n";
	}
	else {
		cout << "NOT A TAUTOLOGY\n";
		cout << falseCount << " out of " << rows << " combinations are FALSE.\n";
	}
	cout << "\n";

	return isTaut;
}

void LogicEngine::addPredicate(const string& name, const string& var1, const string& var2) {
	if (predicateCount >= predicateCapacity) {
		predicateCapacity *= 2;
		string* temp = new string[predicateCapacity];
		for (int i = 0; i < predicateCount; i++)
			temp[i] = predicateNames[i];
		delete[] predicateNames;
		predicateNames = temp;
	}

	string predicate = name + "(" + var1;
	if (var2 != "") {
		predicate += ", " + var2;
	}
	predicate += ")";

	predicateNames[predicateCount++] = predicate;
	cout << "Predicate added: " << predicate << "\n";
}

void LogicEngine::displayPredicates() {
	cout << "\n";
	cout << "PREDICATE LOGIC\n";
	cout << "\n";

	if (predicateCount == 0) {
		cout << "No predicates defined.\n";
		return;
	}

	for (int i = 0; i < predicateCount; i++) {
		cout << (i + 1) << ". " << predicateNames[i] << "\n";
	}

	cout << "\nTotal predicates: " << predicateCount << "\n";
}

bool LogicEngine::checkPredicate(const string& predicateName, const string& arg1, const string& arg2) {
	for (int i = 0; i < factCount; i++) {
		if (facts[i]->predicate == predicateName) {
			if (facts[i]->subject == arg1) {
				if (arg2 == "" || facts[i]->object == arg2) {
					return facts[i]->isTrue;
				}
			}
		}
	}
	return false;
}

bool LogicEngine::universalQuantifier(const string& predicateName, string domain[], int size) {
	cout << "\n";
	cout << "UNIVERSAL QUANTIFIER (ForAll x)\n";
	cout << "\n";
	cout << "Formula: ForAll x " << predicateName << "(x)\n";
	cout << "Meaning: For ALL x in domain, " << predicateName << "(x) is true\n\n";

	bool allTrue = true;

	for (int i = 0; i < size; i++) {
		bool result = checkPredicate(predicateName, domain[i], "");

		cout << "  " << predicateName << "(" << domain[i] << ") = "
			<< (result ? "TRUE" : "FALSE") << "\n";

		if (!result) allTrue = false;
	}

	cout << "\n";
	cout << "Result: " << (allTrue ? "TRUE" : "FALSE") << "\n";
	if (!allTrue) {
		cout << "Reason: At least one element does not satisfy the predicate.\n";
	}
	cout << "\n";

	return allTrue;
}

bool LogicEngine::existentialQuantifier(const string& predicateName, string domain[], int size) {
	cout << "\n";
	cout << "EXISTENTIAL QUANTIFIER (Exists x)\n";
	cout << "\n";
	cout << "Formula: Exists x " << predicateName << "(x)\n";
	cout << "Meaning: There EXISTS at least one x where " << predicateName << "(x) is true\n\n";

	bool existsTrue = false;

	for (int i = 0; i < size; i++) {
		bool result = checkPredicate(predicateName, domain[i], "");

		cout << "  " << predicateName << "(" << domain[i] << ") = "
			<< (result ? "TRUE [OK]" : "FALSE") << "\n";

		if (result) {
			existsTrue = true;
		}
	}

	cout << "\n";
	cout << "Result: " << (existsTrue ? "TRUE" : "FALSE") << "\n";
	if (!existsTrue) {
		cout << "Reason: No element satisfies the predicate.\n";
	}
	cout << "\n";

	return existsTrue;
}

void LogicEngine::demoTautologyAndPredicates() {
	cout << "\n";
	cout << "TAUTOLOGY & PREDICATE LOGIC DEMO\n";
	cout << "\n";

	cout << "\n[PART 1: TAUTOLOGY EXAMPLES]\n";
	cout << "\n--- Example 1: Law of Excluded Middle (P OR NOT P) ---\n";
	isTautology("A|!A");

	cout << "\n--- Example 2: Conjunction (P AND Q) - NOT a tautology ---\n";
	isTautology("A&B");

	cout << "\n[PART 2: PREDICATE LOGIC]\n";
	addPredicate("Student", "x");
	addPredicate("EnrolledIn", "x", "course");
	addPredicate("Completed", "student", "course");
	displayPredicates();

	cout << "\n[PART 3: SAMPLE FACTS]\n";
	addFact("STUDENT", "S001", "Student", "TRUE");
	addFact("STUDENT", "S002", "Student", "TRUE");
	addFact("ENROLLMENT", "S001", "EnrolledIn", "CS1004");
	addFact("COMPLETED", "S001", "Completed", "CS1004");

	cout << "\n[PART 4: QUANTIFIER TESTING]\n";
	string domain[] = { "S001", "S002", "S003" };

	cout << "\n--- Testing Universal Quantifier ---\n";
	universalQuantifier("Student", domain, 3);

	cout << "\n--- Testing Existential Quantifier ---\n";
	existentialQuantifier("Student", domain, 3);

	cout << "\n";
	cout << "DEMO COMPLETED\n";
	cout << "\n";
}