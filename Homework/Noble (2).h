#ifndef CORRECTEDREC07_NOBLE_H
#define CORRECTEDREC07_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Warrior;

    // Simulate the behavior of a noble
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& aNoble); //making output operator a friend

    public:
        Noble(const std::string& name); //overloading default constructor

        const std::string& getName() const; //name getter

        int getArmyStrength() const; //Army strength getter

        void updateArmyStrength(int winnerStrength, int loserStrength); // Update Army strength

        void die(); // Simulates noble dying

        bool hire(Warrior& aWarrior); //Hires a warrior

        bool fire(Warrior& aWarrior); //Fires a warrior

        bool remove(Warrior& aWarrior); //Attempts to remove a warrior

        void battle(Noble& enemy); //Simulates battles between nobles and their armies

    private:
        // private variables of a noble
        std::string name;
        std::vector<Warrior*> army;
        bool alive;
    };
}

#endif //CORRECTEDREC07_NOBLE_H
