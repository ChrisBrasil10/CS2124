#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {

    ostream& operator<<(ostream& os, const Warrior& aWarrior) {
        os << aWarrior.name << ": " << aWarrior.strength;
        return os;
    } //overloading output operator

    Warrior::Warrior(const string& name, int strength)
            : name(name), strength(strength), lord(nullptr), hired(false) {} //overloading Warrior default constructor

    const string& Warrior::getName() const { return name; } //Name getter

    int Warrior::getStrength() const { return strength; } // Strength getter

    void Warrior::setStrength(int theStrength) { strength = theStrength; } //Strength Setter

    void Warrior::setLord(Noble* noblePtr) { lord = noblePtr; } //Lord setter

    Noble* Warrior::getLord() const { return lord; } //Lord getter

    bool Warrior::isHired() const{return hired; }// Checks hired status

    void Warrior::setStatus(bool aBool) {hired = aBool;} //Changes warrior hired status

    bool Warrior::runaway() {
        if (strength == 0) {  // fail if warrior is dead
            cout << name << " is already dead!" << endl;
            return false;
        }
        if (!lord) {  // fail if lord is a nullptr
            cout << name << " doesn't have a lord!";
            return false;
        }
        string nameOfLord = lord->getName();
        if (lord->remove(*this)) {
            cout << name << " flees in terror, abandoning his lord, "
                 << nameOfLord << endl;
            setStatus(false);
            return true;
        }
        return false;  // fail if the warrior is not removed from the army
    } //Simulates a warrior running away
}  // namespace WarriorCraft