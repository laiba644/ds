#include "FunctionsModule.h"
#include <iostream>
using namespace std;
FunctionsModule::FunctionsModule() {
    studentCount = courseCount = facultyCount = roomCount = 0;
    students = courses = faculty = rooms = NULL;
    studentToCourse = courseToFaculty = facultyToRoom = NULL;
}
FunctionsModule::~FunctionsModule() {
    delete[] students;
    delete[] courses;
    delete[] faculty;
    delete[] rooms;
    delete[] studentToCourse;
    delete[] courseToFaculty;
    delete[] facultyToRoom;
}
void FunctionsModule::inputStudents() {
    cout << "How many students? " << endl;
    cin >> studentCount;
    students = new string[studentCount];
    for (int i = 0; i < studentCount; i++) {
        cout << "Student " << (i + 1) << ": ";
        cin >> students[i];
    }
    studentToCourse = new int[studentCount];
}
void FunctionsModule::inputCourses() {
    cout << "How many courses? " << endl;
    cin >> courseCount;
    courses = new string[courseCount];
    for (int i = 0; i < courseCount; i++) {
        cout << "Course " << (i + 1) << ": ";
        cin >> courses[i];
    }
    courseToFaculty = new int[courseCount];
}
void FunctionsModule::inputFaculty() {
    cout << "How many faculty members? " << endl;
    cin >> facultyCount;
    faculty = new string[facultyCount];
    for (int i = 0; i < facultyCount; i++) {
        cout << "Faculty " << (i + 1) << ": ";
        cin >> faculty[i];
    }
    facultyToRoom = new int[facultyCount];
}
void FunctionsModule::inputRooms() {
    cout << "How many rooms? " << endl;
    cin >> roomCount;

    rooms = new string[roomCount];
    for (int i = 0; i < roomCount; i++) {
        cout << "Room " << (i + 1) << ": ";
        cin >> rooms[i];
    }
}
void FunctionsModule::mapStudentToCourse() {
    cout << endl << "Assign student -> course:" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << "Choose course index for " << students[i] << ":" << endl;
        for (int j = 0; j < courseCount; j++)
            cout << "  " << j << ") " << courses[j] << endl;
        cin >> studentToCourse[i];
    }
}
void FunctionsModule::mapCourseToFaculty() {
    cout << endl << "Assign course -> faculty:" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << "Choose faculty index for " << courses[i] << ":" << endl;
        for (int j = 0; j < facultyCount; j++)
            cout << "  " << j << ") " << faculty[j] << endl;

        cin >> courseToFaculty[i];
    }
}
void FunctionsModule::inverseCourseFaculty() {
    cout << endl << "Inverse Mapping: Faculty -> Courses" << endl;
    for (int f = 0; f < facultyCount; f++) {
        cout << faculty[f] << " -> ";
        bool hasCourse = false;
        for (int c = 0; c < courseCount; c++) {
            if (courseToFaculty[c] == f) {
                cout << courses[c] << " ";
                hasCourse = true;
            }
        }
        if (!hasCourse) cout << "No Course Assigned";
        cout << endl;
    }
}

void FunctionsModule::mapFacultyToRoom() {
    cout << endl << "Assign faculty -> room:" << endl;
    for (int i = 0; i < facultyCount; i++) {
        cout << "Choose room index for " << faculty[i] << ":" << endl;
        for (int j = 0; j < roomCount; j++)
            cout << "  " << j << ") " << rooms[j] << endl;

        cin >> facultyToRoom[i];
    }
}
//if two courses are being taught by same faculty not injective
void FunctionsModule::checkInjective() {
    cout << endl << "Checking Injective (One-to-One) " << endl;
    bool ok = true;
    for (int i = 0; i < courseCount; i++)
        for (int j = i + 1; j < courseCount; j++)
            if (courseToFaculty[i] == courseToFaculty[j])
                ok = false;
    cout << (ok ? "Injective" : "NOT Injective") << endl;
}
//Ensure every faculty teaches at least one course
void FunctionsModule::checkSurjective() {
    cout << endl << "Checking Surjective (Onto)" << endl;
    bool* covered = new bool[facultyCount];
    for (int i = 0; i < facultyCount; i++) 
        covered[i] = false;
    for (int i = 0; i < courseCount; i++)
        covered[courseToFaculty[i]] = true;
    bool ok = true;
    for (int i = 0; i < facultyCount; i++)
        if (!covered[i])
            ok = false;
    cout << (ok ? "Surjective" : "NOT Surjective") << endl;
    delete[] covered;
}
/*total courses = total faculty
no duplication*/
void FunctionsModule::checkBijective() {
    cout << endl << "Checking Bijective " << endl;
    bool bij= true;
    if (courseCount != facultyCount)
        bij = false;
    else {
        bool* covered = new bool[facultyCount];
        for (int i = 0; i < facultyCount; i++)
            covered[i] = false;
        for (int i = 0; i < courseCount; i++) {
            if (covered[courseToFaculty[i]])
                bij = false;
            covered[courseToFaculty[i]] = true;
        }
        delete[] covered;
    }
    cout << (bij ? "Bijective" : "NOT Bijective") << endl;
}
void FunctionsModule::composeStudentFaculty() {
    cout << endl << "Composition Result: Student -> Faculty" << endl;
    for (int i = 0; i < studentCount; i++) {
        int courseIdx = studentToCourse[i];
        int facultyIdx = courseToFaculty[courseIdx];
        cout << students[i] << " -> " << faculty[facultyIdx] << endl;
    }
}
void FunctionsModule::displayMappings() {
    cout << endl << "Student -> Course" << endl;
    for (int i = 0; i < studentCount; i++)
        cout << students[i] << " -> " << courses[studentToCourse[i]] << endl;
    cout << endl << "Course -> Faculty" << endl;
    for (int i = 0; i < courseCount; i++)
        cout << courses[i] << " → " << faculty[courseToFaculty[i]] << endl;
    cout << endl << "Faculty -> Room" << endl;
    for (int i = 0; i < facultyCount; i++)
        cout << faculty[i] << " -> " << rooms[facultyToRoom[i]] << endl;
}


