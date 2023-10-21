#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly{

    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name << ": ";
        if (rhs.courses.empty()){
            os << "No Courses";
            return os;
        }
        for (size_t i = 0; i < rhs.courses.size(); i++){
            os << rhs.courses[i]->getName() << " ";
        }
        return os;
    }

    Student::Student(const string &name) : name(name){}

    const string& Student::getName() const {return name;}

    bool Student::addCourse(Course* course){
        for (size_t i = 0; i < courses.size(); i++){
            if (course == courses[i]){
                return false;
            }
        }
        courses.push_back(course);
        return true;
    }

    void Student::removedFromCourse(Course* course) {
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
    }
}
