#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    // Protector Implementation Code
    // initialization list
    Protector::Protector(const string& aName, double theStrength)
            : name(aName), strength(theStrength), lord(nullptr) {}
    //output operator
    ostream& operator<<(ostream& os, const Protector& aProtector);
    // getters and setters
    const string& Protector::getName() const { return name; }
    double Protector::getStrength() const { return strength; }
    void Protector::setStrength(double theStrength) { strength = theStrength; }
    void Protector::setLord(Lord* lordPtr) { lord = lordPtr; }
    Lord* Protector::getLord() const { return lord; }

    // let the Protector runaway
    bool Protector::runaway() {
        if (strength == 0) {  // fail if Protector is dead
            cout << name << " is already dead!" << endl;
            return false;
        }
        if (!lord) {  // fail if lord is a nullptr
            cout << name << " doesn't have a lord!";
            return false;
        }
        string lordName = lord->getName();
        if (lord->remove(*this)) {
            cout << name << " flees in terror, abandoning his lord, "
                 << lordName << endl;
            return true;
        }
        return false;  // fail if the Protector is not removed from the army
    }

    ostream& operator<<(ostream& os, const Protector& aProtector){
        os << aProtector.name << " has a strength " << aProtector.strength;
        return os;
    }

    void Warrior::defend() const {
        cout << getName() << " says: Take that in the name of my lord, "
             << getLord()->getName() << endl;
    }

    // Wizard Implementation Code
    void Wizard::defend() const{
        cout << "POOF!" << endl;
    }

    // Archer Implementation Code
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }

    // Archer Implementation Code
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();
    }
}
