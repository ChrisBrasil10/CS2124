/*
  hw06-single.cpp
  November 2nd 2023
  Chris Brasil
  This program simulates battles between nobles and their army of warriors
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Warrior;

// Simulate the behavior of a noble
class Noble {
    friend ostream& operator<<(ostream& os, const Noble& aNoble); //making output operator a friend

public:
    Noble(const string& name); // Warrior Constructor

    const string& getName() const; //name getter

    int getArmyStrength() const; //army strength getter

    void updateArmyStrength(int winnerStrength, int loserStrength); //updates both army strengths based on ratio

    void die(); //simulates death of a Noble

    bool hire(Warrior& aWarrior); //hires warrior

    bool fire(Warrior& aWarrior); // fires warrior

    bool remove(Warrior& aWarrior); // removes a warrior from army

    void battle(Noble& enemy);  // battle between Noble armies

private:
    // private variables of a noble
    string name;
    vector<Warrior*> army;
    bool alive;
};

// Simulates the behavior of a Warrior
class Warrior {

    friend ostream& operator<<(ostream& os, const Warrior& aWarrior); //making output operator a friend

public:
    Warrior(const string& name, int strength); //Overloading Warrior default constructor

    void setStatus(bool aBool); // changes the hiring status of a Warrior

    const string& getName() const; //name getter

    int getStrength() const; //Gets individual warrior strength

    void setStrength(int strength); //Updates strength of individual warrior

    void setLord(Noble* noblePtr); //assigns a lord to a warrior

    Noble* getLord() const; //Gets the lord of warrior

    bool isHired() const; //Checks if warrior is hired

    bool runaway(); //Simulates a warrior running away

private:
    // private variables of Warrior class
    std::string name;
    int strength;
    Noble* lord;
    bool hired;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}



ostream& operator<<(ostream& os, const Noble& aNoble) {
    os << aNoble.name << " has an army of " << aNoble.army.size()
       << endl;
    for (size_t i = 0; i < aNoble.army.size(); ++i) {
        Warrior* currPtr = aNoble.army[i];
        os << "        " << *currPtr << endl;
    }
    return os;
} //overloading Noble output operator

ostream& operator<<(ostream& os, const Warrior& aWarrior) {
    os << aWarrior.name << ": " << aWarrior.strength;
    return os;
} //overloading Warrior output operator

Noble::Noble(const string& name) : name(name), army(), alive(true) {} //defining Noble constructor

const string& Noble::getName() const { return name; } //Name getter

int Noble::getArmyStrength() const {
    // adds up strengths of all the warriors
    int total_strength = 0;
    for (size_t i = 0; i < army.size(); i++){
        Warrior* const currPtr = army[i];
        total_strength += currPtr->getStrength();
    }
    return total_strength;
} //Army strength getter

void Noble::updateArmyStrength(int winnerStrength, int loserStrength) {
    for (size_t i = 0; i < army.size(); ++i) {
        Warrior* currPtr = army[i];
        int updatedStrength =
                currPtr->getStrength() * (winnerStrength - loserStrength) /
                winnerStrength;
        currPtr->setStrength(updatedStrength);
    }
}


void Noble::die() {
    alive = false;
    updateArmyStrength(1, 1);
}

bool Noble::hire(Warrior& aWarrior) {
    if (!alive) {
        cout << "Noble " << name << " is already dead!" << endl;
        return false;  // returns false if noble is dead
    }
    if (aWarrior.getLord()) {  // if a warriors lord is not a nullptr
        cout << name << " failed to hire " << aWarrior.getName()
             << endl;
        return false;  // returns false if warrior is hired
    }
    aWarrior.setLord(this);
    aWarrior.setStatus(true); // changes status of hired
    army.push_back(&aWarrior);
    return true;
}

bool Noble::fire(Warrior& aWarrior) {
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
} //Attempts to fire warrior

bool Noble::remove(Warrior& aWarrior) {
    for (size_t i = 0; i < army.size(); i++) {
        if (army[i] == &aWarrior) {
            aWarrior.setLord(nullptr);
            army[i] = army.back();  // copy last element to removed
            // warrior's place
            army.pop_back();
            return true;
        }
    }
    cout << aWarrior.getName() << " is not hired by " << name << "!"
         << endl;
    return false;  // fail if the Warrior is not hired by the Noble
} //Attempts to remove warrior from army

void Noble::battle(Noble& enemy) {
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
} //battle between noble and their armies

Warrior::Warrior(const string& name, int strength): name(name), strength(strength), hired(false) {} //overloading
// Warrior constructor

const string& Warrior::getName() const { return name; } //Name getter

int Warrior::getStrength() const { return strength; } //Strength getter

void Warrior::setStrength(int theStrength) { strength = theStrength; } //Strength Setter

void Warrior::setLord(Noble* noblePtr) { lord = noblePtr; } //Sets a lord to a warrior

Noble* Warrior::getLord() const { return lord; } //Lord getter

bool Warrior::isHired() const{return hired; } //Returns warrior hired status

bool Warrior::runaway() {
    if (strength == 0) {  // fail if warrior is dead
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
        hired = false;
        return true;
    }
    return false;  // fail if the warrior is not removed from the army
} //Simulates a warrior running away from lord

void Warrior::setStatus(bool aBool){hired = aBool;} //changes hired status
