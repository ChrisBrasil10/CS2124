#include <iostream>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {

    ostream &operator<<(ostream &os, const Noble &aNoble) {
        os << aNoble.name << " has an army of " << aNoble.army.size()
           << endl;
        for (Warrior *currPtr: aNoble.army) {
            os << "        " << *currPtr << endl;
        }
        return os;
    } //Overloading output operator

    Noble::Noble(const string &name) : name(name), army(), alive(true) {} //Overloading noble default constructor

    const string &Noble::getName() const { return name; } // Noble name getter

    int Noble::getArmyStrength() const {
        int total_strength = 0;
        for (Warrior *const &currPtr: army) {
            total_strength += currPtr->getStrength();
        }
        return total_strength;
    } // Army strength getter

    void Noble::updateArmyStrength(int winnerStrength, int loserStrength) {
        for (Warrior *&currPtr: army) {
            int updatedStrength =
                    currPtr->getStrength() * (winnerStrength - loserStrength) /
                    winnerStrength;
            currPtr->setStrength(updatedStrength);
        }
    } //Update Army Strength
    // with ratio formula

    void Noble::die() {
        alive = false;
        updateArmyStrength(1, 1);
    } //Simulates death of Noble

    bool Noble::hire(Warrior &aWarrior) {
        if (!alive) {
            cout << "Noble " << name << " is already dead!" << endl;
            return false;  // returns false if noble is dead
        }
        if (aWarrior.getLord()) {  // if aWarrior.lord is not a nullptr
            cout << "Warrior " << aWarrior.getName() << " is already hired!"
                 << endl;
            return false;  // returns false if warrior is hired
        }
        aWarrior.setLord(this);
        aWarrior.setStatus(true);
        army.push_back(&aWarrior);
        return true;
    } // attempts to hire a warrior

    bool Noble::fire(Warrior &aWarrior) {
        if (!alive) {
            cout << "Noble " << name << " is already dead!" << endl;
            return false;  // fail if Noble is dead
        }
        if (remove(aWarrior)) {
            cout << aWarrior.getName() << ", you don't work for me anymore "
                 << "! -- " << name << "." << endl;
            aWarrior.setStatus(false);
            return true;
        }
        return false;  // fail if the warrior is not removed
    } //attempts to fire a Warrior

    bool Noble::remove(Warrior &aWarrior) {
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == &aWarrior) {
                aWarrior.setLord(nullptr);
                army[i] = army.back();  // copy last element to removed
                // warrior's place
                army.pop_back();
                return true;
            }
        }
        cout << name << " failed to hire " << aWarrior.getName() << "!"
             << endl;
        return false;  // fail if the Warrior is not hired by the Noble
    } //attempts to remove warrior from army

    void Noble::battle(Noble &enemy) {
        cout << name << " battles " << enemy.name << endl;
        // check whether there's dead nobel(s).
        if (!alive && !enemy.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive && enemy.alive) {
            cout << "He's dead, " << enemy.name << endl;
        } else if (alive && !enemy.alive) {
            cout << "He's dead, " << name << endl;
        } else {  // both nobles are alive
            int selfStrength = getArmyStrength();
            int enemyStrength = enemy.getArmyStrength();
            // determine which noble to die
            if (selfStrength == enemyStrength) {
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << name << " and " << enemy.name
                     << " die at each other's hands" << endl;
            } else if (selfStrength > enemyStrength) {
                updateArmyStrength(selfStrength, enemyStrength);
                enemy.die();
                cout << name << " defeats " << enemy.name << endl;
            } else {  // self_strength < enemy_strength
                enemy.updateArmyStrength(enemyStrength, selfStrength);
                die();
                cout << enemy.name << " defeats " << name << endl;
            }
        }
    } //Simulates battles between nobles and their warrior army
}
