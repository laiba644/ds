#include "CourseScheduling.h"
#include "InductionChecker.h"
#include "CombinationModule.h"
#include "RelationsModule.h"
#include <iostream>
using namespace std;



int main() {

    CourseScheduling uni;
    uni.loadCoursesFromFile("courses.txt");
    uni.loadPrerequisitesFromFile("prerequisites.txt");

    InductionChecker checker(&uni);
    CombinationModule comb;
    RelationsModule rel;

    int choice;

    while (true) {

        cout << "\n=============================================\n";
        cout << "      FAST UNIVERSITY – BSSE SYSTEM MENU\n";
        cout << "=============================================\n";
        cout << "1. Course Scheduling Module\n";
        cout << "2. Induction Checker Module\n";
        cout << "3. Combination (Groups/Labs) Module\n";
        cout << "4. Relations Module\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int ch1;
            cout << "\n--- COURSE SCHEDULING MODULE ---\n";
            cout << "1. Show All Courses\n";
            cout << "2. Semester-wise Valid Plan\n";
            cout << "3. Generate Valid Sequences (subset)\n";
            cout << "Enter option: ";
            cin >> ch1;

            if (ch1 == 1) uni.displayCourses();
            else if (ch1 == 2) uni.generateValidSemesterPlan();
            else if (ch1 == 3) {
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
            cout << "\n--- INDUCTION CHECK MODULE ---\n";

            string target;
            cout << "Enter course code: ";
            cin >> target;
            target = toUpperCase(target);

            string chain[100]; int cnt = 0;
            checker.getFullChain(target, chain, cnt);

            cout << "\nFull Chain:\n";
            for (int i = 0; i < cnt; i++) cout << chain[i] << "\n";

            int c;
            cout << "\nHow many completed? ";
            cin >> c;

            string* completed = new string[c];
            for (int i = 0; i < c; i++) cin >> completed[i];
            for (int i = 0; i < c; i++) completed[i] = toUpperCase(completed[i]);

            if (checker.verifyEligibility(target, completed, c))
                cout << "Allowed.\n";
            else
                cout << "Not Allowed.\n";

            delete[] completed;
        }

        else if (choice == 3) {

            cout << "\n--- COMBINATION MODULE ---\n";
            cout << "1. Add Students\n";
            cout << "2. Display Students\n";
            cout << "3. Generate Project Groups\n";
            cout << "4. Assign Lab Sessions\n";
            cout << "Enter: ";
            int ch2; cin >> ch2;

            if (ch2 == 1) comb.loadStudents();
            else if (ch2 == 2) comb.displayStudents();
            else if (ch2 == 3) {
                int g; cout << "Group size: "; cin >> g;
                comb.generateProjectGroups(g);
            }
            else if (ch2 == 4) {
                int s; cout << "Students per lab: "; cin >> s;
                comb.assignLabSessions(s);
            }
        }

        else if (choice == 4) {

            cout << "\n--- RELATIONS MODULE ---\n";
            cout << "1. Add Students\n";
            cout << "2. Add Courses\n";
            cout << "3. Add Faculty\n";
            cout << "4. Add Rooms\n";
            cout << "5. Add Student-Course Relation\n";
            cout << "6. Add Course-Conflict Relation\n";
            cout << "7. Show Student-Course Matrix\n";
            cout << "8. Show Course-Conflict Matrix\n";
            cout << "9. Analyze Relation Properties\n";
            cout << "10. Detect Indirect Conflicts\n";
            cout << "Enter: ";
            int ch3; cin >> ch3;

            if (ch3 == 1)
                rel.inputStudentsFromConsole();
            else if (ch3 == 2)
                rel.inputCoursesFromConsole();
            else if (ch3 == 3)
                rel.inputFacultyFromConsole();
            else if (ch3 == 4) 
                rel.inputRoomsFromConsole();
            else if (ch3 == 5)
                rel.inputStudentCoursePairs();
            else if (ch3 == 6)
                
                rel.inputCourseConflictPairs();
            else if (ch3 == 7) 
                rel.showStudentCourseRelation();
            else if (ch3 == 8) 
                
                rel.showCourseConflictRelation();
            else if (ch3 == 9) 
                rel.analyzeCourseConflictRelation();
            else if (ch3 == 10) 
                rel.detectIndirectStudentConflicts();
        }

        else if (choice == 5) {
            cout << "\nExiting...\n";
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
