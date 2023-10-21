/*
  hw04.cpp
  October 6th 2023
  Chris Brasil
  This program simulates battles between Nobles and their army of warriors
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior); //making output operator a friend

public:
    Warrior(string const& warriorName, double strength) : warriorName(warriorName), strength(strength), hired(false){}
    // Warrior Constructor

    bool getJobStatus() const {return hired;} // gets warrior job status

    void setJob(){ // sets job to true
        if (!hired){
            hired = true;
        }
    }

    void resetJobStatus(){ // sets job to false
        if (hired){
            hired = false;
        }
    }

    const string& getName(){return warriorName;} // gets warrior name

    double getStrength() const{return strength;} // gets strength of warrior

    void setStrength(double newStrength) {strength = newStrength;} // updates strength of warrior

private:
    double strength;
    string warriorName;
    bool hired;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble); //makes output operator a friend of Noble

public:
    Noble(const string& nobleName) : nobleName(nobleName), status(true), armyStrength(0) {} // Noble Constructor

    bool hire(Warrior& warrior) {  // attempts to hire warriors
        Warrior* warriorPtr = &warrior;
        if (!warrior.getJobStatus() && status){ // if warrior is unemployed
            army.emplace_back(warriorPtr); // adds to army and adds strength to army strength
            armyStrength += warriorPtr->getStrength();
            warriorPtr->setJob();
            return true;
        }
        else{
            cout << nobleName << " has failed to hire " << warrior.getName() << endl; // fails to hire warrior
            return false;
        }
    }

    bool fire(Warrior& warrior) {
        if (!status){
            cout << nobleName << " failed to fire " << warrior.getName() << endl; // if noble is dead, fails to fire
            return false;
        }
        bool found = false;
        for (size_t i=0; i< army.size() ; i++){   // checks if warrior works for Noble
            if (warrior.getName() == army[i]->getName()){
                found = true;
            }
        }
        if (found){ // if warrior works for noble
                bool fired = false;
                for (size_t i = 0; i < army.size(); i++){
                    if (!fired){
                        if (army[i] == &warrior){}
                        cout << "You don't work for me anymore " << warrior.getName() << "! -- " << nobleName << ". "
                             << endl;
                        warrior.resetJobStatus(); // fires warrior
                        fired = true;
                    }
                    else{
                        army[i-1] = army[i]; // shifts warriors
                    }
                    armyStrength -= warrior.getStrength(); // removes warrior from army and removes strength from army strength
                    army.pop_back();
                }
                return fired;
        }
        else { // if warrior doesn't work for noble, fails to fire
            cout << nobleName << " failed to fire " << warrior.getName() << endl;
            return false;
        }
    }

    void kill(){status = false; updateArmy(1,1);} // kills nobles and army

    void updateArmy(double winnerArmy, double loserArmy){
        int newArmyStrength = 0;
        for (Warrior*& warrior : army){ // iterates through army and updates each individual warrior strength
            int newWarriorStrength = warrior->getStrength() * (winnerArmy - loserArmy) / winnerArmy;
            warrior->setStrength(newWarriorStrength);
            newArmyStrength += newWarriorStrength; // adds new warrior strength to new army strength
        }
        armyStrength = newArmyStrength;
    }

    void battle(Noble& otherNoble){
        cout << nobleName << " battles " << otherNoble.nobleName << endl;

        if (!status && !otherNoble.status){ // Both Nobles dead
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else if (!status && otherNoble.status){ // Primary noble dead
            cout << "He's dead " << otherNoble.nobleName << endl;
        }
        else if (status && !otherNoble.status){ // enemy Noble dead
            cout << "He's dead " << nobleName << endl;
        }
        else {
            if (armyStrength == otherNoble.armyStrength){ // If both armies have same strength
                kill();
                otherNoble.kill();
                cout << "Mutual Annihilation " << nobleName << " and " <<
                otherNoble.nobleName << " die at each other's hands" << endl;
            }
            else if (armyStrength > otherNoble.armyStrength) { // if primary army is stronger
                updateArmy(armyStrength, otherNoble.armyStrength);
                otherNoble.kill();
                cout << nobleName << " defeats " << otherNoble.nobleName << endl;
            }
            else { // If enemy army is stronger
                updateArmy(otherNoble.armyStrength, armyStrength);
                kill();
                cout << otherNoble.nobleName << " defeats " << nobleName << endl;
            }
        }
    }

private:
    string nobleName;
    vector <Warrior*> army;
    bool status;
    double armyStrength;
};

int main() {

   Noble art("King Arthur");
   Noble lance("Lancelot du Lac");
   Noble jim("Jim");
   Noble linus("Linus Torvalds");
   Noble billie("Bill Gates");

   Warrior cheetah("Tarzan", 10);
   Warrior wizard("Merlin", 15);
   Warrior theGovernator("Conan", 12);
   Warrior nimoy("Spock", 15);
   Warrior lawless("Xena", 20);
   Warrior mrGreen("Hulk", 8);
   Warrior dylan("Hercules", 3);

   jim.hire(nimoy);
   lance.hire(theGovernator);
   art.hire(wizard);
   lance.hire(dylan);
   linus.hire(lawless);
   billie.hire(mrGreen);
   art.hire(cheetah);
   art.hire(nimoy);

   cout << "==========\n\n"
        << "Status before all battles, etc.\n";
   cout << jim << endl;
   cout << lance << endl;
   cout << art << endl;
   cout << linus << endl;
   cout << billie << endl;
   cout << "==========\n\n";

   art.fire(cheetah);
   cout << art << endl;

   lance.fire(nimoy);
   cout << lance << endl;
   cout << "==========\n\n";

   art.battle(lance);
   jim.battle(lance);
   linus.battle(billie);
   billie.battle(lance);

   cout << "==========\n\n"
        << "Status after all battles, etc.\n";
   cout << jim << endl;
   cout << lance << endl;
   cout << art << endl;
   cout << linus << endl;
   cout << billie << endl;
   cout << "==========\n";

}

ostream& operator<<(ostream& os, const Warrior& warrior){ // overloading Warrior output operator
    os << warrior.warriorName << ": " << warrior.strength;
    return os;
}

ostream& operator<<(ostream& os, const Noble& noble){ // overloading Noble output operator
    os << noble.nobleName << " has an army of " << noble.army.size() << '\n';
    for (size_t i = 0; i <noble.army.size(); i++){
        os << "\t" << *noble.army[i] << endl;
    }
    return os;
}
