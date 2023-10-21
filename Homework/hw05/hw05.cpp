/*
 hw05.cpp
 October 12, 2023
 Chris Brasil
 This program simulates battles between Nobles and their army of warriors by using dynamic memory allocation.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


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
        if (!status) {
            cout << nobleName << " failed to fire " << warrior.getName() << endl; // If noble is dead, fails to fire
            return false;
        }

        bool found = false;
        size_t warriorIndex = 0; // We'll keep track of the index of the warrior to fire.

        for (size_t i = 0; i < army.size(); i++) { // Check if the warrior works for the noble
            if (warrior.getName() == army[i]->getName()) {
                found = true;
                warriorIndex = i; // Store the index of the warrior to fire.
                break; // No need to continue searching.
            }
        }

        if (found) { // If warrior works for noble
            cout << warrior.getName() << ", you don't work for me anymore! -- " << nobleName << ".\n";
            warrior.resetJobStatus(); // Fire the warrior
            armyStrength -= warrior.getStrength(); // Remove warrior's strength from army strength

            // Shift the remaining warriors in the army to fill the gap.
            for (size_t i = warriorIndex; i < army.size() - 1; i++) {
                army[i] = army[i + 1];
            }

            army.pop_back(); // Remove the last warrior since it's a duplicate.
            return true; // Warrior has been fired.
        } else { // If the warrior doesn't work for the noble, fails to fire
            cout << nobleName << " failed to fire " << warrior.getName() << endl;
            return false;
        }
    }

    int getArmyCount() {return army.size();}

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

    const string& getName(){ return nobleName;}

    bool warriorChecker(const string& warriorName){
        for (size_t i = 0; i < army.size(); i++) {
            if (warriorName == army[i]->getName()){
                return true;
            }
        }
        return false;
    }

private:
    string nobleName;
    vector <Warrior*> army;
    bool status;
    double armyStrength;
};

// Define a function to find a warrior by name in a vector
Warrior* warriorFinder(const string& warriorName, const vector <Warrior*>& warriorVector);

// Define a function to find a noble by name in a vector
Noble* nobleFinder(const string& nobleName, const vector <Noble*>& nobleVector);

// Define a function to clear the noble vector and free memory
void clearNoble(vector <Noble*>& nobleVector);

// Define a function to clear the warrior vector and free memory
void clearWarrior(vector <Warrior*>& warriorVector);

// Define a function to display the status of nobles and warriors
void displayStatus(const vector <Warrior*>& warriorVector, const vector<Noble*>& nobleVector);

// Define a function to handle firing a warrior from a noble's army
void mainFire(const string& nobleName, const string& warriorName, const vector<Noble*>& nobleVector, const vector<Warrior*>& warriorVector);

// Define a function to handle a battle between two nobles
void mainBattle(const string& firstNobleName, const string& secondNobleName, const vector<Noble*>& nobleVector);

// Define a function to handle hiring a warrior by a noble
void mainHire(const string& nobleName, const string& warriorName, const vector <Noble*>& nobleVector, const vector <Warrior*>& warriorVector);

int main() {
    // Open the input file for reading noble and warrior information
    ifstream noblesFile;
    vector <Warrior*> warriorVector;
    vector <Noble*> nobleVector;

    noblesFile.open("nobleWarriors.txt");
    if (!noblesFile){
        cerr << "File could not be found " << endl;
    }
    string token;

    // Read tokens from the input file and process them
    while (noblesFile >> token){
        if (token == "Noble"){
            // Read noble name from the input file
            string nobleName;
            noblesFile >> nobleName;
            if (!nobleFinder(nobleName, nobleVector)){
                nobleVector.emplace_back(new Noble(nobleName));
            }
            else{
                cout << nobleName << " is already taken!" << endl;
            }
        }
        else if (token == "Warrior"){
            // Read warrior name and strength from the input file
            string warriorName;
            double warriorStrength;
            noblesFile >> warriorName >> warriorStrength;
            if (!nobleFinder(warriorName, nobleVector)){
                warriorVector.emplace_back(new Warrior(warriorName, warriorStrength));
            }
            else {
                cout << warriorName << " is already taken!" << endl;
            }
        }
        else if (token == "Hire"){
            // Read noble name and warrior name and hire the warrior for the noble
            string nobleName;
            string warriorName;
            noblesFile >> nobleName >> warriorName;
            mainHire(nobleName, warriorName, nobleVector, warriorVector);
        }
        else if (token == "Fire"){
            // Read noble name and warrior name and fire the warrior from the noble's army
            string nobleName;
            string warriorName;
            noblesFile >> nobleName >> warriorName;
            mainFire(nobleName, warriorName, nobleVector, warriorVector);
        }
        else if (token == "Status"){
            // Display the status of nobles and warriors
            displayStatus(warriorVector, nobleVector);
        }
        else if (token == "Battle"){
            // Read names of two nobles and simulate a battle between them
            string firstNobleName;
            string secondNobleName;
            noblesFile >> firstNobleName >> secondNobleName;
            mainBattle(firstNobleName, secondNobleName, nobleVector);
        }
        else {
            // Clear both warrior and noble vectors
            clearWarrior(warriorVector);
            clearNoble(nobleVector);
        }
    }
    noblesFile.close(); //Close file
    clearWarrior(warriorVector); //Clear warrior vector
    clearNoble(nobleVector); // Clear noble vector
    return 0;
}

// Overload the output operator for the Warrior class
ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "\t" << warrior.warriorName << ": " << warrior.strength;
    return os;
}

// Overload the output operator for the Noble class
ostream& operator<<(ostream& os, const Noble& noble){
    os << noble.nobleName << " has an army of " << noble.army.size() << '\n';
    for (size_t i = 0; i <noble.army.size(); i++){
        os << "\t" << *noble.army[i] << endl;
    }
    return os;
}

// Function to find a warrior by name in a vector
Warrior* warriorFinder(const string& warriorName, const vector <Warrior*>& warriorVector){
    for (size_t i = 0; i < warriorVector.size(); i++){
        if (warriorName == warriorVector[i]->getName()){
            return warriorVector[i];
        }
    }
    return nullptr;
}

// Function to find a noble by name in a vector
Noble* nobleFinder(const string& nobleName, const vector <Noble*>& nobleVector){
    for (size_t i = 0; i < nobleVector.size(); i++){
        if (nobleName == nobleVector[i]->getName()){
            return nobleVector[i];
        }
    }
    return nullptr;
}

// Function to clear the warrior vector and free memory
void clearWarrior(vector <Warrior*>& warriorVector){
    for (size_t i = 0; i < warriorVector.size(); i++) {
        delete warriorVector[i];
    }
    warriorVector.clear();
}

// Function to clear the noble vector and free memory
void clearNoble(vector <Noble*>& nobleVector) {
    for (size_t i = 0; i < nobleVector.size(); i++) {
        delete nobleVector[i];
    }
    nobleVector.clear();
}

// Function to display the status of nobles and warriors
void displayStatus(const vector <Warrior*>& warriorVector, const vector<Noble*>& nobleVector){
    cout << "Status \n" << "====== \n" << "Nobles:" << endl;

    int warriorCount = 0;
    if (!nobleVector.empty()){
        for (size_t i = 0; i < nobleVector.size(); i++){
            cout << *nobleVector[i];
            warriorCount += nobleVector[i]->getArmyCount();
        }
    }
    else{
        cout << "NONE" << endl;
    }
    cout << "\n" << "Unemployed Warriors:" << endl;
    if (warriorVector.size() - warriorCount > 0 ){
        for (size_t i = 0; i < warriorVector.size(); i++){
            if (!warriorVector[i]->getJobStatus()) {
                cout << "\t" << *warriorVector[i] << endl;
            }
        }
    }
    else{
        cout << "NONE" << endl;
    }
}

// Function to handle firing a warrior from a noble's army
void mainFire(const string& nobleName, const string& warriorName, const vector<Noble*>& nobleVector, const vector<Warrior*>& warriorVector){
    if (nobleFinder(nobleName, nobleVector) && warriorFinder(warriorName, warriorVector)) {
        Noble *aNoble = nobleFinder(nobleName, nobleVector);
        Warrior *aWarrior = warriorFinder(warriorName, warriorVector);
        if (aNoble->warriorChecker(warriorName)){
            aNoble->fire(*aWarrior);
        }
        else{
            cout << warriorName << " is not hired by you " << nobleName << endl;
        }
    }
    else if (!nobleFinder(nobleName, nobleVector)){
        cout << "Attempting to fire using unknown noble: " << nobleName << endl;
    }
    else {
        cout << "Attempting to fire using unknown warrior: " << warriorName << endl;
    }
}

// Function to handle a battle between two nobles
void mainBattle(const string& firstNobleName, const string& secondNobleName, const vector<Noble*>& nobleVector){
    if (nobleFinder(firstNobleName, nobleVector) && nobleFinder(secondNobleName, nobleVector)) {
        Noble* aNoble = nobleFinder(firstNobleName, nobleVector);
        Noble* anotherNoble = nobleFinder(secondNobleName, nobleVector);
        aNoble->battle(*anotherNoble);
    }
    else if (!nobleFinder(firstNobleName, nobleVector)){
        cout << "Attempting to battle using unknown noble: " << firstNobleName << endl;
    }
    else {
        cout << "Attempting to battle against an unknown noble: " << secondNobleName << endl;
    }
}

// Function to handle hiring a warrior by a noble
void mainHire(const string& nobleName, const string& warriorName,
              const vector <Noble*>& nobleVector, const vector <Warrior*>& warriorVector){
    if (nobleFinder(nobleName, nobleVector) && warriorFinder(warriorName, warriorVector)) {
        Noble *aNoble = nobleFinder(nobleName, nobleVector);
        Warrior *aWarrior = warriorFinder(warriorName, warriorVector);
        aNoble->hire(*aWarrior);
    }
    else if (!nobleFinder(nobleName, nobleVector)){
        cout << "Attempting to hire using unknown noble: " << nobleName << endl;
    }
    else {
        cout << "Attempting to hire using unknown warrior: " << warriorName << endl;
    }
}
