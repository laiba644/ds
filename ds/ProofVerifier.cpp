#include "ProofVerifier.h"
#include <iostream>
using namespace std;
ProofVerifier::ProofVerifier(CourseScheduling* s, InductionChecker* i, LogicEngine* l) {
    sys = s;
    indu = i;
    logic = l;
}
void ProofVerifier::proveCourseEligibility(const string& course, string completed[], int cCount) {
    cout << "\nFORMAL INDUCTION PROOF: " << course << " n";
    string chain[200]; 
    int count = 0;
    indu->getFullChain(course, chain, count);
    if (count == 0) {
        cout << "No prerequisites. Proof complete.\n";
        return;
    }
    cout << "\nStep 1 (Basis):\n";
    cout << "Check smallest prerequisite: " << chain[0] << "\n";
    bool basis = false;
    for (int i = 0;i < cCount;i++)
        if (chain[0] == completed[i])
            basis = true;
    cout << (basis ? " Basis holds\n" : " Basis failed\n");
    cout << "\nStep 2 (Inductive Step):\n";
    bool ok = true;
    for (int i = 0;i < count;i++) {
        bool has = false;
        for (int j = 0;j < cCount;j++)
            if (chain[i] == completed[j])
                has = true;
        cout << "Check: Student completed " << chain[i] << " ?  ";
        cout << (has ? " True\n" : " False\n");
        if (!has) 
            ok = false;
    }
    cout << "\nConclusion:\n";
    cout << (ok ? "Therefore student is allowed to take " : "Therefore student is NOT allowed to take ");
    cout << course << "\n";
}
void ProofVerifier::proveLogicRule(int index) {
    cout << "\n=== LOGIC RULE VERIFICATION ===\n";
    cout << "Rule" << index + 1 << "\n";
    logic->verifyAllRules();
}
void ProofVerifier::proveFacultyLabConsistency(const string& course) {
    cout << "\n=== RELATIONAL CONSISTENCY PROOF ===\n";
    cout << "Course: " << course << "\n";
    bool ok = logic->verifyLabAllocation(course, "LAB_A");
    bool ok2 = logic->verifyFacultyAssignment("FACULTY_X", course);
    cout << "Check Faculty Assigned → ";
    cout << (ok2 ? " Holds\n" : " Violated\n");
    cout << "Check Required Lab → ";
    cout << (ok ? " Holds\n" : " Violated\n");
    cout << "\nConclusion: ";
    cout << ((ok && ok2) ? "Mapping is consistent.\n" : "Mapping is NOT consistent.\n");
}
