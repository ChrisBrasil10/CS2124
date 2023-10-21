/*
  Chris Brasil
  rec05-start.cpp
  October 6th, 2023
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section{
    class TimeSlot;
    class StudentRecord;

    friend ostream& operator <<(ostream& os, const Section& section);
    friend ostream& operator<<(ostream& os, const Section::TimeSlot& labTimeSlot);
    friend ostream& operator<<(ostream& os, const Section::StudentRecord& student);

    class StudentRecord{
        friend ostream& operator<<(ostream& os, const Section::StudentRecord& student);

        public:
            StudentRecord(const string& studentName): studentName(studentName), studentGradeList(14, -1) {}
            const string& getStudentName() const {return studentName;}
            void updateGrade(int newGrade, const int weekNumber){
                if ((weekNumber >= 1) && (weekNumber - 1 <= studentGradeList.size())){
                    studentGradeList[weekNumber-1] = newGrade;
                }
                else{
                    cout << "Invalid Week Number" << endl;
                }
            }
        private:
            vector<int> studentGradeList;
            string studentName;
    };

    class TimeSlot{

        friend ostream& operator<< (ostream& os, const TimeSlot& labTimeSlot);
        public:
            TimeSlot(const string& dayOfWeek, const unsigned timeOfDay): dayOfWeek(dayOfWeek), timeOfDay(timeOfDay){}

        private:
            string dayOfWeek;
            unsigned timeOfDay;
    };

public:
    Section(const string& sectionName, const string& dayOfWeek, const unsigned timeOfDay)
            : sectionName(sectionName), labTimeSlot(dayOfWeek, timeOfDay){}

    Section(const Section& other) : sectionName(other.sectionName), labTimeSlot(other.labTimeSlot) {
        for (size_t i = 0; i < other.studentList.size(); i++) {
            studentList.push_back(new StudentRecord(*(other.studentList[i])));
        }
    }
    ~Section(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        this->reset();
    }

    void addStudent(string const& studentName){
        StudentRecord* student;
        student  = new StudentRecord(studentName);
        studentList.emplace_back(student);
    }
    void addGrade(const string& studentName, int gradeValue, int weekNumber){
        for (size_t i = 0; i < studentList.size(); i++) {
            if (studentList[i]->getStudentName() == studentName) {
                studentList[i]->updateGrade(gradeValue, weekNumber);
            }
        }
    }

    void reset(){
        for (size_t i = 0; i < studentList.size(); i++) {
            cout << "Deleting " << studentList[i]->getStudentName() << endl;
            delete studentList[i];
        }
        studentList.clear();
    }

private:
    string sectionName;
    TimeSlot labTimeSlot;
    vector <StudentRecord*> studentList;
};

class LabWorker{
    friend ostream& operator <<(ostream& os, const LabWorker& labWorker);
public:
    LabWorker(string const& workerName): workerName(workerName) {}

    void addSection(Section& sectionName){
        sectionPtr = &sectionName;
    }
    void addGrade(const string& studentName, int gradeValue, int weekNumber){
        if (sectionPtr == nullptr) {
            cout << "No section assigned to " << workerName << ". Cannot add grade." << endl;
            return;
        }
        sectionPtr->addGrade(studentName, gradeValue, weekNumber);
    }
private:
    string workerName;
    Section* sectionPtr = nullptr;
};

void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";


    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main


ostream& operator <<(ostream& os, const Section& section){
    os << "Section " << section.sectionName << ", " << section.labTimeSlot << ", ";
    if (section.studentList.empty()){
        os << "Students: None " << endl;
    }
    else{
        os << "Students: " << endl;
        for (size_t i = 0; i < section.studentList.size(); i++){
            os << *(section.studentList[i]) << endl;
        }
    }
    return os;
}

ostream& operator<< (ostream& os, const Section::TimeSlot& labTimeSlot){
    if (labTimeSlot.timeOfDay > 12){
        os << "Time slot: [Day: " << labTimeSlot.dayOfWeek << ", Start time: " << labTimeSlot.timeOfDay - 12 << "pm]";
        return os;
    }
    else {
        os << "Time slot: [Day: " << labTimeSlot.dayOfWeek << ", Start time: " << labTimeSlot.timeOfDay << "am]";
        return os;
    }}

ostream& operator<<(ostream& os, const Section::StudentRecord& student){
    os << student.studentName << ", Grades: ";
    for (size_t i = 0; i < student.studentGradeList.size(); i++){
        os << student.studentGradeList[i] << " ";
    }
    return os;
}

ostream& operator <<(ostream& os, const LabWorker& labWorker){
    os << labWorker.workerName << " " ;
    if (labWorker.sectionPtr == nullptr){
        os << "does not have a section" << endl;
    }
    else {
        os << "has " << *labWorker.sectionPtr << endl;
    }
    return os;
}
