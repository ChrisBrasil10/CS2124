#ifndef CORRECTEDREC07_WARRIOR_H
#define CORRECTEDREC07_WARRIOR_H

#include <fstream>
#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;

    // Simulates the behavior of a Warrior
    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, const Warrior& aWarrior); //making output operator a friend

    public:
        Warrior(const std::string& name, int strength); //overloading Warrior default constructor

        const std::string& getName() const; //name Getter

        int getStrength() const; // Strength Getter

        Noble* getLord() const; //Lord Getter

        void setStrength(int strength); //Strength Setter

        void setLord(Noble* noblePtr); // Lord Setter

        bool isHired() const; //return warrior hired status

        bool runaway(); //Simulates a warrior running away

        void setStatus(bool aBool); //Changes hired status of a warrior

    private:
        // private variables of Warrior class
        std::string name;
        int strength;
        Noble* lord;
        bool hired;
    };
}
#endif //CORRECTEDREC07_WARRIOR_H
