#ifndef CORRECTEDREC07_COURSE_H
#define CORRECTEDREC07_COURSE_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Student;

    class Course{
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);

        const std::string& getName() const;

        bool addStudent(Student* student);

        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };
}


#endif //CORRECTEDREC07_COURSE_H
