#include <iostream>
#include <vector>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    // Noble Implementation Code
    // initialization list
    Noble::Noble(const string& theName) : name(theName), alive(true) {}
    //output operator
    ostream& operator<<(ostream& os, const Noble& aNoble);
    // getters and setters
    const string& Noble::getName() const { return name; }
    void Noble::changeAliveStatus() { alive = !alive; }
    bool Noble::getAliveStatus() const { return alive; }

    // Battle between Nobles
    void Noble::battle(Noble& enemy) {
        cout << name << " battles " << enemy.name << endl;
        //Check different situations
        if (!alive && !enemy.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive && enemy.alive) {
            enemy.defend();
            cout << "He's dead, " << enemy.name << endl;
        } else if (alive && !enemy.alive) {
            defend();
            cout << "He's dead, " << name << endl;
        } else {  // both Nobles are alive
            double selfStrength = getStrength();
            double enemyStrength = enemy.getStrength();
            defend();
            enemy.defend();
            if (selfStrength == enemyStrength) {
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << name << " and " << enemy.name
                     << " die at each other's hands" << endl;
            } else if (selfStrength > enemyStrength) {
                updateStrength(selfStrength, enemyStrength);
                enemy.die();
                cout << name << " defeats " << enemy.name << endl;
            } else {  // selfStrength < enemyStrength
                enemy.updateStrength(enemyStrength, selfStrength);
                die();
                cout << enemy.name << " defeats " << name << endl;
            }
        }
    }

    void Noble::die() {  // change the status of "alive" and set strength to 0
        changeAliveStatus();
        updateStrength(1, 1);
    }

    std::ostream& operator<<(std::ostream& os, const Noble& aNoble) {
        os << aNoble.getName();
        aNoble.display(os);
        return os;
    }

    // Lord Implementation Code
    Lord::Lord(const std::string& aName) : Noble(aName) {}
    double Lord::getStrength() const {
        // sum up strengths of all the Warriors in the army and return
        double total_strength = 0;
        for (Protector* currPtr : army) {
            total_strength += currPtr->getStrength();
        }
        return total_strength;
    }

    // multiply strength of each Protector with the ratio
    void Lord::updateStrength(double winnerStrength, double loserStrength) {
        for (Protector* currPtr : army) {
            double updatedStrength =
                    currPtr->getStrength() * (winnerStrength - loserStrength) /
                    winnerStrength;  // current strength times the ratio
            currPtr->setStrength(updatedStrength);
        }
    }

    // call defend() for every Protector
    void Lord::defend() const {
        for (Protector* currPtr : army) {
            currPtr->defend();
        }
    }

    // hire a Protector
    bool Lord::hires(Protector& aProtector) {
        if (!getAliveStatus()) {
            return false;  // fail if Noble is dead
        }
        if (aProtector.getLord()) {  // if somewarrior.lord is not a nullptr
            return false;  // fail if Warrior is already hired
        }
        aProtector.setLord(this);
        army.push_back(&aProtector);
        return true;
    }

    // fire a Protector
    bool Lord::fires(Protector& aProtector) {
        if (!getAliveStatus()) {
            return false;  // fail if Lord is dead
        }
        if (remove(aProtector)) {
            cout << aProtector.getName() << ", you don't work for me anymore! -- "
                 << getName() << "." << endl;
            return true;
        }
        return false;  // fail if the protector is not removed
    }

    // remove a protector (fire or runaway)
    bool Lord::remove(Protector& aProtector) {
        size_t i = 0;
        for (; i < army.size(); ++i) {
            if (army[i] == &aProtector) {
                aProtector.setLord(nullptr);
                break;
            }
        }
        if (i < army.size()) {
            for (; i < army.size() - 1; ++i) {
                army[i] = army[i + 1];
            }
            army.pop_back();
            return true;
        }
        cout << aProtector.getName() << " is not hired by " << getName() << "!" << endl;
        return false;
    }

    void Lord::display(std::ostream& os) const{
        os << " has an army of size: " << army.size();
        for (int i{}; i < army.size(); i++){
            os << "\n\t" << *army[i];
        }
    }

    // PersonWithStrengthToFight Implementation Code
    PersonWithStrengthToFight::PersonWithStrengthToFight(
            const std::string& theName, double theStrength)
            : Noble(theName), strength(theStrength) {}

    // getter and setter
    double PersonWithStrengthToFight::getStrength() const { return strength; }

    void PersonWithStrengthToFight::updateStrength(double winnerStrength,
                                                   double loserStrength) {

        strength = winnerStrength - loserStrength;
    }

    void PersonWithStrengthToFight::defend() const { cout << "Ugh!" << endl; }
    void PersonWithStrengthToFight::display(std::ostream& os) const{
        os << " has strength: " << getStrength();
    }
}
