#ifndef COURSESCHEDULING_H
#define COURSESCHEDULING_H
#include <iostream>
#include <string>
using namespace std;
string toUpperCase(string s);
class CourseScheduling {
public:
    class Course {
    public:
        string courseCode;
        string courseName;
        
        int credits;
        string type;
        int semester;
        string* prerequisites;
        int prereqCount;
        int prereqCapacity;
        Course();
        Course(const string& code, const string& name, int cred, const string& type, int sem);
        ~Course();
        void addPrerequisite(const string& prereq);
        void print() const;
    }; 
    Course** courses;
    int** prerequisiteMatrix;
    int courseCount;
    int courseCapacity;
    CourseScheduling();
    ~CourseScheduling();
    void resizeCourses();
    void addCourse(const string& code, const string& name, int credits, const string& type, int semester);
    Course* findCourse(const string& code);
    int getCourseIndex(const string& code);
    void loadCoursesFromFile(const string& filename);
    void loadPrerequisitesFromFile(const string& filename);
    void displayCourses();
    bool canTakeCourse(const string& courseCode, string* completed, int completedCount);
    bool isValidSequence(string* seq, int size);
    void generateValidSemesterPlan();
    void generateSubsetSequences(string subset[], int count);
    void subsetPermuteHelper(string* selected, bool* used, string* curr, int depth, int count, int& printed);
   
};
#endif
