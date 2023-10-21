/*
  Chris Brasil
  rec07.cpp
  October 20, 2023
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;
class Registrar;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);

    const string& getName() const;

    bool addStudent(Student* student);

    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name) : name(name) {vector<Course*> courses;};

    const string& getName() const;

    bool addCourse(Course* course);

    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar(): courses(vector<Course*>()), students(vector<Student*>()) {}

    bool addCourse(const string& courseName);

    bool addStudent(const string& studentName);

    bool enrollStudentInCourse(const string& studentName, const string& courseName);

    bool cancelCourse(const string& courseName);

    void purge();

private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& courseName) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;


    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
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
//Course methods
Course::Course(const std::string &courseName): name(courseName) {}

bool Course::addStudent(Student *student) {
    bool checker = false;
    for (size_t i = 0; i < students.size(); i++) {
        if (student == students[i]) {
            checker = true;
            break;
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

//Student Methods
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

//Registrar Methods
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
    return student->addCourse(course) && course->addStudent(student);
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