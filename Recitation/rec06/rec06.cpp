/*
  rec06.cpp
  Chris Brasil
  October 13, 2023
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;


// Position class
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary) : title(aTitle), salary(aSalary) {}

    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// Directory class
class Directory {
    // nested Entry class
    class Entry {
        friend ostream& operator<<(ostream& os, const Entry& rhs) {
            os << rhs.name << ' ' << rhs.room
               << ' ' << rhs.phone << ", " << *rhs.pos;
            return os;
        }
    public:
        Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {}

        const string& getName() const { return name; }
        unsigned getPhone() const { return phone; }
    private:
        string name;
        unsigned room;
        unsigned phone;
        Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    friend ostream& operator<<(ostream& os, const Directory& rhs){
        os << "Directory: " << rhs.company << endl;
        for (size_t i = 0; i < rhs.size; i ++){
            os << *rhs.entries[i] << endl;
        }
        return os;
    }


public:
     Directory(const string& company):
            company(company), size(0), capacity(1), entries(nullptr) {}

    ~Directory() {
        for (size_t i = 0; i< size; i++){
            delete entries[i];
        }
        delete[] entries;
    }

    Directory(const Directory& directory) : company(directory.company) {

        size = directory.size;
        capacity = directory.capacity;
        entries = new Entry*[capacity];

        // copy
        for (size_t i = 0; i < size; i++) {
            entries[i] = new Entry(*directory.entries[i]) ;
        }
    }

    Directory& operator=(const Directory& directory){
        if (this != &directory) {
            // deallocate
            for (size_t i = 0; i< size; i++){
                delete entries[i];
            }

            delete[] entries;

            // allocate
            size = directory.size;
            capacity = directory.capacity;
            entries = new Entry*[capacity];
            // copy (deep);
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*directory.entries[i]);
            }
        }
        return *this;
    }

    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (entries == nullptr){
            entries = new Entry* [capacity];
        }
        if (size == capacity) {
            capacity = capacity * 2;

            // Create a new array of Entry pointers
            Entry **newentries = new Entry *[capacity];

            // Copy data from the old array to the new array
            for (int i = 0; i < size; i++) {
                newentries[i] = entries[i];
            }

            // Delete the old array
            delete[] entries;

            // Update entries to point to the new array
            entries = newentries;
        }

        // Create a new Entry and add it to the array
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    }

    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; i++){
            if (name ==  entries[i]->getName()){
                return entries[i]->getPhone();
            }
        }
        return 99999;
    }

private:
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory

void doNothing(Directory dir) {
     cout << dir << endl;
}

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);


    // Create a Directory
    Directory d("HAL");
    // Add someone
    d.add("Marilyn", 123, 4567, boss);
    // print the directory
    cout << d << endl;
    // Use the square bracket operator, aka the Index operator,
    // to access someone's phone extension.

    cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
    cout << "======\n\n";

    // Everything working so far? Get checked out!!!

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;



    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);


    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;

} // main
