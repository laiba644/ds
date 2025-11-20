#include "RelationsModule.h"
#include <iostream>
using namespace std;

RelationsModule::RelationsModule() {
    studentCapacity = 10;
    studentCount = 0;
    students = new string[studentCapacity];

    courseCount = 0;
    facultyCount = 0;
    roomCount = 0;

    initMatrices();
}

void RelationsModule::initMatrices() {
    int i;

    studentCourse = new int* [MAX_STUDENTS];
    for (i = 0; i < MAX_STUDENTS; i++)
        studentCourse[i] = new int[MAX_COURSES];
    clearMatrix(studentCourse, MAX_STUDENTS, MAX_COURSES);

    facultyCourse = new int* [MAX_FACULTY];
    for (i = 0; i < MAX_FACULTY; i++)
        facultyCourse[i] = new int[MAX_COURSES];
    clearMatrix(facultyCourse, MAX_FACULTY, MAX_COURSES);

    courseRoom = new int* [MAX_COURSES];
    for (i = 0; i < MAX_COURSES; i++)
        courseRoom[i] = new int[MAX_ROOMS];
    clearMatrix(courseRoom, MAX_COURSES, MAX_ROOMS);

    courseConflict = new int* [MAX_COURSES];
    for (i = 0; i < MAX_COURSES; i++)
        courseConflict[i] = new int[MAX_COURSES];
    clearMatrix(courseConflict, MAX_COURSES, MAX_COURSES);
}

void RelationsModule::clearMatrix(int** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = 0;
}

RelationsModule::~RelationsModule() {
    delete[] students;

    for (int i = 0; i < MAX_STUDENTS; i++)
        delete[] studentCourse[i];
    delete[] studentCourse;

    for (int i = 0; i < MAX_FACULTY; i++)
        delete[] facultyCourse[i];
    delete[] facultyCourse;

    for (int i = 0; i < MAX_COURSES; i++)
        delete[] courseRoom[i];
    delete[] courseRoom;

    for (int i = 0; i < MAX_COURSES; i++)
        delete[] courseConflict[i];
    delete[] courseConflict;
}

void RelationsModule::resizeStudents() {
    studentCapacity *= 2;
    string* temp = new string[studentCapacity];

    for (int i = 0; i < studentCount; i++)
        temp[i] = students[i];

    delete[] students;
    students = temp;
}

int RelationsModule::findStudent(const string& name) const {
    for (int i = 0; i < studentCount; i++)
        if (students[i] == name)
            return i;
    return -1;
}

int RelationsModule::findCourse(const string& code) const {
    for (int i = 0; i < courseCount; i++)
        if (courses[i] == code)
            return i;
    return -1;
}

int RelationsModule::findFaculty(const string& name) const {
    for (int i = 0; i < facultyCount; i++)
        if (faculty[i] == name)
            return i;
    return -1;
}

int RelationsModule::findRoom(const string& roomName) const {
    for (int i = 0; i < roomCount; i++)
        if (rooms[i] == roomName)
            return i;
    return -1;
}

void RelationsModule::addStudent(const string& name) {
    if (studentCount >= MAX_STUDENTS) return;
    if (studentCount >= studentCapacity) resizeStudents();
    students[studentCount++] = name;
}

void RelationsModule::addCourse(const string& code) {
    if (courseCount >= MAX_COURSES) return;
    courses[courseCount++] = code;
}

void RelationsModule::addFaculty(const string& name) {
    if (facultyCount >= MAX_FACULTY) return;
    faculty[facultyCount++] = name;
}

void RelationsModule::addRoom(const string& roomName) {
    if (roomCount >= MAX_ROOMS) return;
    rooms[roomCount++] = roomName;
}

void RelationsModule::inputStudentsFromConsole() {
    int n; cout << "\nHow many students? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string name; cin >> name;
        addStudent(name);
    }
}

void RelationsModule::inputCoursesFromConsole() {
    int n; cout << "\nHow many courses? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string code; cin >> code;
        addCourse(code);
    }
}

void RelationsModule::inputFacultyFromConsole() {
    int n; cout << "\nHow many faculty members? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string name; cin >> name;
        addFaculty(name);
    }
}

void RelationsModule::inputRoomsFromConsole() {
    int n; cout << "\nHow many rooms? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string rn; cin >> rn;
        addRoom(rn);
    }
}

void RelationsModule::addStudentCoursePair(const string& studentName, const string& courseCode) {
    int si = findStudent(studentName);
    int ci = findCourse(courseCode);
    if (si == -1 || ci == -1) return;
    studentCourse[si][ci] = 1;
}

void RelationsModule::addFacultyCoursePair(const string& facultyName, const string& courseCode) {
    int fi = findFaculty(facultyName);
    int ci = findCourse(courseCode);
    if (fi == -1 || ci == -1) return;
    facultyCourse[fi][ci] = 1;
}

void RelationsModule::addCourseRoomPair(const string& courseCode, const string& roomName) {
    int ci = findCourse(courseCode);
    int ri = findRoom(roomName);
    if (ci == -1 || ri == -1) return;
    courseRoom[ci][ri] = 1;
}

void RelationsModule::addCourseConflictPair(const string& c1, const string& c2) {
    int i1 = findCourse(c1);
    int i2 = findCourse(c2);
    if (i1 == -1 || i2 == -1) return;
    courseConflict[i1][i2] = 1;
    courseConflict[i2][i1] = 1;
}

void RelationsModule::inputStudentCoursePairs() {
    int m; cout << "\nHow many pairs? "; cin >> m;
    for (int i = 0; i < m; i++) {
        string s, c; cin >> s >> c;
        addStudentCoursePair(s, c);
    }
}

void RelationsModule::inputCourseConflictPairs() {
    int m; cout << "\nHow many conflicts? "; cin >> m;
    for (int i = 0; i < m; i++) {
        string c1, c2; cin >> c1 >> c2;
        addCourseConflictPair(c1, c2);
    }
}

void RelationsModule::showStudentCourseRelation() {
    cout << "\n";
    if (studentCount == 0 || courseCount == 0) return;

    for (int j = 0; j < courseCount; j++)
        cout << courses[j] << " ";
    cout << "\n";

    for (int i = 0; i < studentCount; i++) {
        cout << students[i] << " : ";
        for (int j = 0; j < courseCount; j++)
            cout << studentCourse[i][j] << " ";
        cout << "\n";
    }
}

void RelationsModule::showCourseConflictRelation() {
    cout << "\n";
    if (courseCount == 0) return;

    for (int j = 0; j < courseCount; j++)
        cout << courses[j] << " ";
    cout << "\n";

    for (int i = 0; i < courseCount; i++) {
        cout << courses[i] << " : ";
        for (int j = 0; j < courseCount; j++)
            cout << courseConflict[i][j] << " ";
        cout << "\n";
    }
}

bool RelationsModule::isReflexive(int** rel, int n) const {
    for (int i = 0; i < n; i++)
        if (rel[i][i] == 0) return false;
    return true;
}

bool RelationsModule::isSymmetric(int** rel, int n) const {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (rel[i][j] == 1 && rel[j][i] == 0) return false;
    return true;
}

bool RelationsModule::isTransitive(int** rel, int n) const {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (rel[i][j] == 1)
                for (int k = 0; k < n; k++)
                    if (rel[j][k] == 1 && rel[i][k] == 0)
                        return false;
    return true;
}

bool RelationsModule::isAntisymmetric(int** rel, int n) const {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && rel[i][j] == 1 && rel[j][i] == 1) return false;
    return true;
}

void RelationsModule::analyzeCourseConflictRelation() {
    if (courseCount == 0) 
        return;

    bool refl = isReflexive(courseConflict, courseCount);
    bool symm = isSymmetric(courseConflict, courseCount);
    bool trans = isTransitive(courseConflict, courseCount);
    bool anti = isAntisymmetric(courseConflict, courseCount);

    cout << "\nReflexive? " << (refl ? "Yes" : "No");
    cout << "\nSymmetric? " << (symm ? "Yes" : "No");
    cout << "\nTransitive? " << (trans ? "Yes" : "No");
    cout << "\nAntisymmetric? " << (anti ? "Yes" : "No");

    cout << "\nEquivalence? " << ((refl && symm && trans) ? "Yes" : "No");
    cout << "\nPartial Order? " << ((refl && anti && trans) ? "Yes" : "No");
    cout << "\n";
}

void RelationsModule::detectIndirectStudentConflicts() {
    if (studentCount == 0 || courseCount == 0) return;

    int** studConflict = new int* [studentCount];
    for (int i = 0; i < studentCount; i++) {
        studConflict[i] = new int[courseCount];
        for (int j = 0; j < courseCount; j++)
            studConflict[i][j] = 0;
    }

    for (int s = 0; s < studentCount; s++) {
        for (int k = 0; k < courseCount; k++) {
            int val = 0;
            for (int j = 0; j < courseCount; j++) {
                if (studentCourse[s][j] == 1 && courseConflict[j][k] == 1) {
                    val = 1;
                    break;
                }
            }
            studConflict[s][k] = val;
        }
    }

    bool anyConflict = false;

    for (int s = 0; s < studentCount; s++) {
        bool hasConflict = false;

        for (int c = 0; c < courseCount; c++) {
            if (studentCourse[s][c] == 1 && studConflict[s][c] == 1) {
                for (int j = 0; j < courseCount; j++) {
                    if (j != c &&
                        studentCourse[s][j] == 1 &&
                        courseConflict[j][c] == 1) {

                        cout << "Student " << students[s]
                            << " has conflicting courses: "
                            << courses[j] << " and " << courses[c] << "\n";

                        hasConflict = true;
                        anyConflict = true;
                        break;
                    }
                }
            }
            if (hasConflict) break;
        }

        if (!hasConflict)
            cout << "Student " << students[s] << ": no conflicts.\n";
    }

    if (!anyConflict)
        cout << "\nNo indirect conflicts detected.\n";

    for (int i = 0; i < studentCount; i++)
        delete[] studConflict[i];
    delete[] studConflict;
}
