#ifndef RELATIONSMODULE_H
#define RELATIONSMODULE_H
#include <iostream>
#include <string>
using namespace std;
class RelationsModule {
private:
    static const int MAX_STUDENTS = 50;
    static const int MAX_COURSES = 50;
    static const int MAX_FACULTY = 20;
    static const int MAX_ROOMS = 20;

    string* students;
    int studentCount;
    int studentCapacity;

    string courses[MAX_COURSES];
    int courseCount;

    string faculty[MAX_FACULTY];
    int facultyCount;

    string rooms[MAX_ROOMS];
    int roomCount;

    int** studentCourse;
    int** facultyCourse;
    int** courseRoom;
    int** courseConflict;

    void initMatrices();
    void clearMatrix(int** mat, int rows, int cols);
    void resizeStudents();

    int findStudent(const string& name) const;
    int findCourse(const string& code) const;
    int findFaculty(const string& name) const;
    int findRoom(const string& roomName) const;

    bool isReflexive(int** rel, int n) const;
    bool isSymmetric(int** rel, int n) const;
    bool isTransitive(int** rel, int n) const;
    bool isAntisymmetric(int** rel, int n) const;

public:
    RelationsModule();
    ~RelationsModule();

    void addStudent(const string& name);
    void addCourse(const string& code);
    void addFaculty(const string& name);
    void addRoom(const string& roomName);

    void inputStudentsFromConsole();
    void inputCoursesFromConsole();
    void inputFacultyFromConsole();
    void inputRoomsFromConsole();

    void addStudentCoursePair(const string& studentName, const string& courseCode);
    void addFacultyCoursePair(const string& facultyName, const string& courseCode);
    void addCourseRoomPair(const string& courseCode, const string& roomName);
    void addCourseConflictPair(const string& course1, const string& course2);

    void inputStudentCoursePairs();
    void inputCourseConflictPairs();

    void showStudentCourseRelation();
    void showCourseConflictRelation();

    void analyzeCourseConflictRelation();
    void detectIndirectStudentConflicts();
};

#endif
