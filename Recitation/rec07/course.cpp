#include <iostream>
#include <string>
#include "course.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Course& rhs){
        os << rhs.name << ": ";
        if (rhs.students.empty()){
            os << "No Students";
            return os;
        }
        for (size_t i = 0; i < rhs.students.size(); i++){
            os << rhs.students[i]->getName();
        }
        return os;
    }

    Course::Course(const std::string &courseName): name(courseName) {}

    bool Course::addStudent(Student *student) {
        bool checker = false;
        for (size_t i = 0; i < students.size(); i++) {
            if (student == students[i]) {
                checker = true;
            }
        }
        if (checker){
            cout << "Failed to add student: Student already in course" << endl;
            return false;
        }
        students.push_back(student);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (size_t i=0; i < students.size(); i++){
            students[i]->removedFromCourse(this);
        }
        students.clear();
    }

    const string& Course::getName() const{return name;}
}
