#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "CombinationModule.h"
#include "RelationsModule.h"
#include "FunctionsModule.h"
#include "LogicEngine.h"
#include "ProofVerifier.h"
#include "SetOperations.h"
#include <iostream>
using namespace std;
int main() {
    CourseScheduling uni;
    uni.loadCoursesFromFile("courses.txt");
    uni.loadPrerequisitesFromFile("prerequisites.txt");
    InductionChecker checker(&uni);
    CombinationModule comb;
    RelationsModule rel;
    FunctionsModule func;
    LogicEngine logic(&uni);
    ProofVerifier proof(&uni, &checker, &logic);
    SetOperations sets;

    int choice;
    do {
        cout << endl;
        cout << " FAST UNIVERSITY – BSSE MENU" << endl;
        cout << "1) Course Scheduling" << endl;
        cout << "2) Induction Checker" << endl;
        cout << "3) Combinations & Groups" << endl;
        cout << "4) Relations Module" << endl;
        cout << "5) Functions & Mappings" << endl;
        cout << "6) Logic & Inference Engine" << endl;
        cout << "7) Automated Proof & Verification" << endl;
        cout << "8) Set Operations" << endl;
        cout << "9) Exit" << endl;
        cout << "Choose option: ";

        cin >> choice;
        if (choice == 1) {
            int c;
            cout << endl;
            cout << " COURSE SCHEDULING " << endl;
            cout << "1) Show All Courses" << endl;
            cout << "2) Generate Semester Plan" << endl;
            cout << "3) Generate Valid Subset Sequences" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1) 
                uni.displayCourses();
            else if (c == 2) 
                uni.generateValidSemesterPlan();
            else if (c == 3) {
                int n;
                cout << "How many courses? ";
                cin >> n;
                string* arr = new string[n];
                for (int i = 0; i < n; i++) cin >> arr[i];
                for (int i = 0; i < n; i++) arr[i] = toUpperCase(arr[i]);
                uni.generateSubsetSequences(arr, n);
                delete[] arr;
            }
        }

        else if (choice == 2) {
            cout << endl;
            cout << " INDUCTION CHECKER " << endl;
            string target;
            cout << "Course Code: ";
            cin >> target;
            target = toUpperCase(target);

            string chain[100];
            int count = 0;
            checker.getFullChain(target, chain, count);

            cout << "Full Chain:" << endl;
            for (int i = 0; i < count; i++)
                cout << chain[i] << endl;

            int done;
            cout << "How many completed? ";
            cin >> done;

            string* arr = new string[done];
            for (int i = 0; i < done; i++) 
                cin >> arr[i];
            for (int i = 0; i < done; i++) 
                arr[i] = toUpperCase(arr[i]);

            cout << (checker.verifyEligibility(target, arr, done) ? "Allowed" : "Not Allowed") << endl;
            delete[] arr;
        }

        else if (choice == 3) {
            int c;
            cout << endl;
            cout << " COMBINATIONS MODULE " << endl;
            cout << "1) Add Students" << endl;
            cout << "2) Display Students" << endl;
            cout << "3) Generate Project Groups" << endl;
            cout << "4) Assign Lab Sessions" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1) 
                comb.loadStudents();
            else if (c == 2)
                comb.displayStudents();
            else if (c == 3) 
            { 
                int g; cout << "Group Size: "; cin >> g; comb.generateProjectGroups(g); 
            }
            else if (c == 4) { 
                int s; cout << "Students per Lab: "; cin >> s; comb.assignLabSessions(s);
            }
        }

        else if (choice == 4) {
            int c;
            cout << endl;
            cout << " RELATIONS MODULE " << endl;
            cout << "1) Add Students" << endl;
            cout << "2) Add Courses" << endl;
            cout << "3) Add Faculty" << endl;
            cout << "4) Add Rooms" << endl;
            cout << "5) Add Student-Course Relation" << endl;
            cout << "6) Add Course-Conflict Relation" << endl;
            cout << "7) Show Student-Course Matrix" << endl;
            cout << "8) Show Course-Conflict Matrix" << endl;
            cout << "9) Check Relation Properties" << endl;
            cout << "10) Detect Indirect Conflicts" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1)
                rel.inputStudentsFromConsole();
            else if (c == 2) 
                rel.inputCoursesFromConsole();
            else if (c == 3) 
                rel.inputFacultyFromConsole();
            else if (c == 4) 
                rel.inputRoomsFromConsole();
            else if (c == 5) 
                rel.inputStudentCoursePairs();
            else if (c == 6) 
                rel.inputCourseConflictPairs();
            else if (c == 7) 
                rel.showStudentCourseRelation();
            else if (c == 8) 
                rel.showCourseConflictRelation();
            else if (c == 9) 
                rel.analyzeCourseConflictRelation();
            else if (c == 10)
                rel.detectIndirectStudentConflicts();
        }

        else if (choice == 5) {
            int c;
            cout << endl;
            cout << "FUNCTIONS & MAPPINGS " << endl;
            cout << "1) Input Students" << endl;
            cout << "2) Input Courses" << endl;
            cout << "3) Input Faculty" << endl;
            cout << "4) Input Rooms" << endl;
            cout << "5) Map Student -> Course" << endl;
            cout << "6) Map Course -> Faculty" << endl;
            cout << "7) Map Faculty -> Room" << endl;
            cout << "8) Inverse: Faculty -> Courses" << endl;
            cout << "9) Check Injective" << endl;
            cout << "10) Check Surjective" << endl;
            cout << "11) Check Bijective" << endl;
            cout << "12) Composition Student -> Faculty" << endl;
            cout << "13) Display All Mappings" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1)
                func.inputStudents();
            else if (c == 2) 
                func.inputCourses();
            else if (c == 3)
                func.inputFaculty();
            else if (c == 4)
                func.inputRooms();
            else if (c == 5) 
                func.mapStudentToCourse();
            else if (c == 6)
                func.mapCourseToFaculty();
            else if (c == 7) 
                func.mapFacultyToRoom();
            else if (c == 8) 
                func.inverseCourseFaculty();
            else if (c == 9) 
                func.checkInjective();
            else if (c == 10)
                func.checkSurjective();
            else if (c == 11)
                func.checkBijective();
            else if (c == 12) 
                func.composeStudentFaculty();
            else if (c == 13) 
                func.displayMappings();
        }

        else if (choice == 6) {
            int c;
            cout << endl;
            cout << "--- LOGIC & INFERENCE ENGINE ---" << endl;
            cout << "1) Load Default Rules" << endl;
            cout << "2) Add Rule" << endl;
            cout << "3) Display Rules" << endl;
            cout << "4) Forward Chaining" << endl;
            cout << "5) Add Fact" << endl;
            cout << "6) Display Facts" << endl;
            cout << "7) Display Knowledge Base" << endl;
            cout << "8) Check Tautology" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1) logic.loadDefaultRules();
            else if (c == 2) {
                string t, a, b; 
                cout << "Type: "; 
                cin >> t;
                cout << "IF: "; 
                cin >> a >> b; string cond = a + " " + b; cout << "THEN: "; cin >> a >> b; string concl = a + " " + b; logic.addRule(t, cond, concl); 
            }
            else if (c == 3) logic.displayRules();
            else if (c == 4) logic.forwardChaining();
            else if (c == 5) { 
                string t, s, p, o;
                bool tr = true;
                cout << "Type Subject Predicate Object: ";
                cin >> t >> s >> p >> o;
                logic.addFact(t, s, p, o, tr);
            }
            else if (c == 6) 
                logic.displayFacts();
            else if (c == 7) 
                logic.displayKnowledgeBase();
            else if (c == 8) { 
                string prop;
                cout << "Enter Proposition: ";
                cin >> prop; 
                logic.isTautology(prop);
            }
        }
        else if (choice == 7) {
            int c;
            cout << endl;
            cout << " AUTOMATED PROOF & VERIFICATION " << endl;
            cout << "1) Proof of Course Eligibility (Induction)" << endl;
            cout << "2) Verify All Logic Rules" << endl;
            cout << "3) Check Faculty-Lab Consistency" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1) {
                string course;
                cout << "Course Code: ";
                cin >> course;
                int n;
                cout << "How many completed? ";
                cin >> n;
                string* Arr = new string[n];
                for (int i = 0; i < n; i++) cin >> Arr[i];
                proof.proveCourseEligibility(toUpperCase(course), Arr, n);
                delete[] Arr;
            }
            else if (c == 2) {
                proof.proveLogicRule(0);
            }
            else if (c == 3) {
                string course;
                cout << "Course Code: ";
                cin >> course;
                proof.proveFacultyLabConsistency(toUpperCase(course));
            }
        }
        else if (choice == 8) {
            int c;
            cout << "--- SET OPERATIONS ---" << endl;
            cout << "1) Create Set" << endl;
            cout << "2) Add Element to Set" << endl;
            cout << "3) Display Set" << endl;
            cout << "4) Display All Sets" << endl;
            cout << "5) Union" << endl;
            cout << "6) Intersection" << endl;
            cout << "7) Difference" << endl;
            cout << "8) Power Set" << endl;
            cout << "9) Cartesian Product" << endl;
            cout << "10) Test University Scenario" << endl;
            cout << "Select: ";
            cin >> c;

            if (c == 1) {
                string n; cout << "Set Name: "; cin >> n; sets.createSet(n);
            }
            else if (c == 2) {
                string n, e; cout << "Set Name: "; cin >> n; cout << "Element: "; cin >> e; sets.addElementToSet(n, e);
            }
            else if (c == 3) {
                string n; cout << "Set Name: "; cin >> n; sets.displaySet(n);
            }
            else if (c == 4) sets.displayAllSets();
            else if (c == 5) {
                string a, b; cout << "A: "; cin >> a; cout << "B: "; cin >> b; sets.unionSets(a, b);
            }
            else if (c == 6) {
                string a, b; cout << "A: "; cin >> a; cout << "B: "; cin >> b; sets.intersectionSets(a, b);
            }
            else if (c == 7) {
                string a, b; cout << "A: "; cin >> a; cout << "B: "; cin >> b; sets.differenceSets(a, b);
            }
            else if (c == 8) {
                string a; cout << "Set: "; cin >> a; sets.generatePowerSet(a);
            }
            else if (c == 9) {
                string a, b; cout << "A: "; cin >> a; cout << "B: "; cin >> b; sets.cartesianProduct(a, b);
            }
            else if (c == 10) sets.testUniversityScenario();
            }



    } while (choice != 9);

    cout << "Goodbye!" << endl;//checkkk
    return 0;
}
