#ifndef PROOFVERIFIER_H
#define PROOFVERIFIER_H
#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "LogicEngine.h"
#include <string>
using namespace std;

class ProofVerifier {
private:
    CourseScheduling* sys;
    InductionChecker* indu;
    LogicEngine* logic;

public:
    ProofVerifier(CourseScheduling*, InductionChecker*, LogicEngine*);
    void proveCourseEligibility(const string& course, string completed[], int cCount);
    void proveLogicRule(int ruleIndex);
    void proveFacultyLabConsistency(const string& course);
};
#endif
