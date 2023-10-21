#include <iostream>
#include <string>
#include <vector>
#include "course.h"
#include "registrar.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report " << endl;
        os << "Courses:" << endl;
        for (size_t i = 0; i < rhs.courses.size(); i++){
            os << *rhs.courses[i] << endl;
        }
        os << "Students: " << endl;
        for (size_t i = 0; i < rhs.students.size(); i++){
            os << *rhs.students[i] << endl;
        }
        return os;
    }

    Registrar::Registrar() {}

    bool Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) == courses.size()){
            courses.push_back(new Course(courseName));
            return true;
        }
        cout << "Failed to add course: Course already exists" << endl;
        return false;
    }

    bool Registrar::addStudent(const string& studentName){
        if (findStudent(studentName) == students.size()){
            students.push_back(new Student(studentName));
            return true;
        }
        cout << "Failed to add student: Student already exists" << endl;
        return false;

    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if (studentIndex == students.size()){
            cout << "Failed to Enroll: student doesn't exist" << endl;
            return false;
        }
        if (courseIndex == courses.size()) {
            cout << "Failed to Enroll: course doesn't exist" << endl;
            return false;
        }
        Course* course = courses[courseIndex];
        Student* student = students[studentIndex];
        student->addCourse(course);
        course->addStudent(student);
        return true;
    }

    bool Registrar::cancelCourse(const string& courseName){
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == courses.size()){
            cout << "Failed to cancel course: Course doesn't exist" << endl;
            return false;
        }
        Course* course = courses[courseIndex];
        course->removeStudentsFromCourse();
        delete course;
        course = nullptr;
        size_t indexToShift = courses.size();
        for (size_t i = 0; i < courses.size(); i++){
            if (course == courses[i]){
                indexToShift = i;
            }
            if (indexToShift != courses.size()){
                courses[i] = courses[i+1];
            }
        }
        courses.pop_back();
        return true;
    }

    void Registrar::purge(){
        for (size_t i = 0; i < courses.size(); i ++){
            delete courses[i];
        }
        courses.clear();
        for (size_t i = 0; i < students.size(); i ++){
            delete students[i];
        }
        students.clear();
    }

    size_t Registrar::findStudent(const string& studentName) const{
        for (size_t i=0; i < students.size(); i++){
            if (studentName == students[i]->getName()){
                return i;
            }
        }
        return students.size();
    }
    size_t Registrar::findCourse(const string& courseName) const{
        for (size_t i=0; i < courses.size(); i++){
            if (courseName == courses[i]->getName()){
                return i;
            }
        }
        return courses.size();
    }
}
