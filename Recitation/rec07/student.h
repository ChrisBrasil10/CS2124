#ifndef CORRECTEDREC07_STUDENT_H
#define CORRECTEDREC07_STUDENT_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly {
    class Course;

    class Student {
        friend std::ostream &operator<<(std::ostream &os, const Student &rhs);

    public:
        // Student methods needed by Registrar
        Student(const std::string &name);

        const std::string &getName() const;

        bool addCourse(Course *course);

        void removedFromCourse(Course *course);

    private:
        std::string name;
        std::vector<Course *> courses;
    };
}

#endif //CORRECTEDREC07_STUDENT_H
