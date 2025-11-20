#ifndef INDUCTIONCHECKER_H
#define INDUCTIONCHECKER_H
#include <string>
using namespace std;
class CourseScheduling;   // forward declaration
class InductionChecker {

private:
    CourseScheduling* sys;   // pointer to Module-1 system

    void dfsAll(int index, bool visited[]);

public:
    
    // Constructor that receives pointer to Module-1 object
    InductionChecker(CourseScheduling* ptr);

    void getFullChain(const string& course,
        string chain[], int& chainCount);

    bool verifyEligibility(const string& targetCourse,
        string completed[], int completedCount);
};

#endif
