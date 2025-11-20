#ifndef FUNCTIONSMODULE_H
#define FUNCTIONSMODULE_H
#include <string>
using namespace std;
class FunctionsModule {
private:
    string* students;
    string* courses;
    string* faculty;
    string* rooms;
    int* studentToCourse;    // Student  Course
    int* courseToFaculty;    // Course  Faculty
    int* facultyToRoom;      // Faculty Room
    int studentCount;
    int courseCount;
    int facultyCount;
    int roomCount;
public:
    FunctionsModule();
    ~FunctionsModule();
    void inputStudents();
    void inputCourses();
    void inputFaculty();
    void inputRooms();
    void mapStudentToCourse();
    void mapCourseToFaculty();
    void mapFacultyToRoom();
    void checkInjective();     // One-to-one
    void checkSurjective();    // Onto
    void checkBijective();     // One-to-one & Onto
    // Function Composition
    void composeStudentFaculty();  // Student Faculty
	void inverseCourseFaculty();  // Faculty Course
    void displayMappings();
};
#endif
