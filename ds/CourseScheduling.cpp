#include "CourseScheduling.h"
#include <fstream>
#include <sstream>
using namespace std;
string toUpperCase(string s) {
    for (int i = 0; i < s.length(); i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    return s;
}

CourseScheduling::Course::Course() {
    credits = 0;
    prereqCount = 0;
    prereqCapacity = 5;
    prerequisites = new string[prereqCapacity];
}
CourseScheduling::Course::Course(const string& code, const string& name, int cred, const string& t, int sem) {
    courseCode = code;
    courseName = name;
    credits = cred;
    type = t;
    semester = sem;

    prereqCount = 0;
    prereqCapacity = 5;
    prerequisites = new string[prereqCapacity];
}

CourseScheduling::Course::~Course() {
    delete[] prerequisites;
}

void CourseScheduling::Course::addPrerequisite(const string& prereq) {
    if (prereqCount >= prereqCapacity) {
        prereqCapacity *= 2;
        string* temp = new string[prereqCapacity];

        for (int i = 0; i < prereqCount; i++)
            temp[i] = prerequisites[i];

        delete[] prerequisites;
        prerequisites = temp;
    }
    prerequisites[prereqCount++] = prereq;
}
void CourseScheduling::Course::print() const {
    cout << courseCode << " | " << courseName << " | "
        << credits << " CrHrs | " << type << " | Semester " << semester << endl;
}
CourseScheduling::CourseScheduling() {
    courseCount = 0;
    courseCapacity = 50;
    courses = new Course * [courseCapacity];
    prerequisiteMatrix = new int* [courseCapacity];
    for (int i = 0; i < courseCapacity; i++) {
        prerequisiteMatrix[i] = new int[courseCapacity];
        for (int j = 0; j < courseCapacity; j++)
            prerequisiteMatrix[i][j] = 0;
    }
}
CourseScheduling::~CourseScheduling() {
    for (int i = 0; i < courseCount; i++)
        delete courses[i];
    delete[] courses;
    for (int i = 0; i < courseCapacity; i++)
        delete[] prerequisiteMatrix[i];
    delete[] prerequisiteMatrix;
}
void CourseScheduling::resizeCourses() {
    int newCap = courseCapacity * 2;
    Course** newArr = new Course * [newCap];
    for (int i = 0; i < courseCount; i++)
        newArr[i] = courses[i];
    delete[] courses;
    courses = newArr;
    int** newMatrix = new int* [newCap];
    for (int i = 0; i < newCap; i++) {
        newMatrix[i] = new int[newCap];
        for (int j = 0; j < newCap; j++)
            newMatrix[i][j] = (i < courseCapacity && j < courseCapacity)
            ? prerequisiteMatrix[i][j]
            : 0;
    }
    for (int i = 0; i < courseCapacity; i++)
        delete[] prerequisiteMatrix[i];
    delete[] prerequisiteMatrix;
    prerequisiteMatrix = newMatrix;
    courseCapacity = newCap;
}
void CourseScheduling::addCourse(const string& code, const string& name, int credits, const string& type, int semester) {
    if (courseCount >= courseCapacity)
        resizeCourses();
    courses[courseCount++] = new Course(code, name, credits, type, semester);
}
CourseScheduling::Course* CourseScheduling::findCourse(const string& code) {
    for (int i = 0; i < courseCount; i++)
        if (courses[i]->courseCode == code)
            return courses[i];
    return nullptr;
}
int CourseScheduling::getCourseIndex(const string& code) {
    for (int i = 0; i < courseCount; i++)
        if (courses[i]->courseCode == code)
            return i;

    return -1;
}
void CourseScheduling::loadCoursesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) 
            continue;
        string code, name, cred, type, sem;
        stringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, cred, ',');
        getline(ss, type, ',');
        getline(ss, sem, ',');
        code = toUpperCase(code);
        addCourse(code, name, stoi(cred), type, stoi(sem));
    }
    file.close();
    cout << "Courses loaded.\n";
}
void CourseScheduling::loadPrerequisitesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) 
            continue;
        string course, prereq;
        stringstream ss(line);
        getline(ss, course, ',');
        getline(ss, prereq, ',');
        course = toUpperCase(course);
        prereq = toUpperCase(prereq);
        int i = getCourseIndex(course);
        int j = getCourseIndex(prereq);
        if (i != -1 && j != -1) {
            courses[i]->addPrerequisite(prereq);
            prerequisiteMatrix[i][j] = 1;
        }
    }
    file.close();
    cout << "Prerequisites loaded.\n";
}
void CourseScheduling::displayCourses() {
    cout << "\n FAST COURSES (Semester-wise)\n";
    for (int sem = 1; sem <= 8; sem++) {
        cout << "\nSemester " << sem << ":\n";
        for (int i = 0; i < courseCount; i++)
            if (courses[i]->semester == sem)
                courses[i]->print();
    }
}
bool CourseScheduling::canTakeCourse(const string& code, string* completed, int completedCount) {
    Course* c = findCourse(code);
    if (!c) 
        return false;
    for (int i = 0; i < c->prereqCount; i++) {
        bool done = false;
        for (int j = 0; j < completedCount; j++)
            if (completed[j] == c->prerequisites[i])
                done = true;
        if (!done) 
            return false;
    }
    return true;
}
bool CourseScheduling::isValidSequence(string* seq, int size) {
    string* done = new string[size];
    int doneCount = 0;
    for (int i = 0; i < size; i++) {
        if (!canTakeCourse(seq[i], done, doneCount)) {
            delete[] done;
            return false;
        }
        done[doneCount++] = seq[i];
    }
    delete[] done;
    return true;
}
void CourseScheduling::subsetPermuteHelper(string* selected, bool* used, string* curr, int depth, int count, int& printed) {
    if (printed >= 10)
        return;
    if (depth == count) {
        if (isValidSequence(curr, count)) {
            printed++;
            cout << printed << ". ";
            for (int i = 0; i < count; i++) {
                cout << curr[i];
                if (i != count - 1) cout << " -> ";
            }
            cout << "\n";
        }
        return;
    }
    for (int i = 0; i < count; i++) {
        if (!used[i]) {
            used[i] = true;
            curr[depth] = selected[i];
            subsetPermuteHelper(selected, used, curr, depth + 1, count, printed);
            used[i] = false;
        }
    }
}
void CourseScheduling::generateSubsetSequences(string subset[], int count) {
    cout << "\n VALID SEQUENCES FOR SELECTED COURSES \n";
    string* selected = new string[count];
    string* curr = new string[count];
    bool* used = new bool[count];
    for (int i = 0; i < count; i++) {
        selected[i] = subset[i];
        selected[i] = toUpperCase(subset[i]);
        used[i] = false;
        if (findCourse(selected[i]) == nullptr) {
            cout << " Error Course " << selected[i] << " does not exist.\n";
            return;
        }
    }
    int printed = 0;
    subsetPermuteHelper(selected, used, curr, 0, count, printed);
    if (printed == 0) {
        cout << " No valid orderings found (prerequisite mismatch)\n";
    }
    cout << "\n";
    delete[] selected;
    delete[] curr;
    delete[] used;
}
void CourseScheduling::generateValidSemesterPlan() {
    string* completed = new string[courseCount];
    int completedCount = 0;
    cout << "\n SEMESTER-WISE VALID PLAN \n";
    for (int sem = 1; sem <= 8; sem++) {
        cout << "\n Semester " << sem << " \n";
        for (int i = 0; i < courseCount; i++) {
            Course* c = courses[i];
            if (c->semester != sem)
                continue;
            cout << "\nCourse: " << c->courseCode << " - " << c->courseName << "\n";
            if (c->prereqCount == 0) {
                cout << "Prerequisites: None\n";
                cout << "Status: Allowed \n";
                completed[completedCount++] = c->courseCode;
                continue;
            }
            cout << "Prerequisites: ";
            bool allCompleted = true;
            for (int j = 0; j < c->prereqCount; j++) {
                string pre = c->prerequisites[j];
                cout << pre;
                bool done = false;
                for (int k = 0; k < completedCount; k++)
                    if (completed[k] == pre)
                        done = true;
                if (!done) {
                    allCompleted = false;
                    cout << " (Missing)";
                }
                if (j != c->prereqCount - 1) cout << ", ";
            }
            cout << "\n";
            if (allCompleted) {
                cout << "Status: Allowed \n";
                completed[completedCount++] = c->courseCode;
            }
            else {
                cout << "Status: NOT Allowed \n";
            }
        }
    }
    delete[] completed;
}
