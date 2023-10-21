/*
  hw02.cpp
  Septemebr 22, 2023
  Chris Brasil
  Simulate battles between warriors
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Warrior {
    // Contructs a warrior struct
    Warrior(const string& theName, int theStrength)
            : name(theName), strength(theStrength) {}
    string name;
    int strength;
};

void fileOpener(ifstream& file);
void displayWarriorVector(const vector<Warrior>& warriorVector);
void warriorBattle(Warrior& warrior1, Warrior& warrior2);
void updateWarriorStats(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior>& warriorVector);
Warrior searchForWarrior(const string& name, const vector<Warrior>& warriorVector);
Warrior constructWarrior(const string& name, int strength);
int main() {
    ifstream warriorFile;
    fileOpener(warriorFile);
    string command;
    vector<Warrior> warriorVector;

    while (warriorFile >> command) {
        // checking for key commands (warrior, status, and battle)
        if (command == "Warrior") {
            // takes name and strength, then creates a warrior object. Lastly adds it to a vector
            string name;
            int strength;
            warriorFile >> name >> strength;
            bool nameTaken = false;
            for (const Warrior &currentWarrior: warriorVector) {
                if (currentWarrior.name == name) {
                    nameTaken = true;
                    break;
                }
            }
            if (!nameTaken) {
                // Create and add the warrior if the name is not taken
                warriorVector.push_back(constructWarrior(name, strength));
            } else {
                cout << "Error: Warrior name '" << name << "' is already taken." << endl;
            }
        }
        else if (command == "Status") {
            // displays the status of all warriors
            displayWarriorVector(warriorVector);
        }
        else {
            // takes names of two warriors, checks if they both exist, commence the battle between both warriors..
            // finally updates their stats in the warrior vector
            string warriorName1, warriorName2;
            warriorFile >> warriorName1 >> warriorName2;

            bool warrior1Found = false;
            bool warrior2Found = false;

            // Check if both warriors exist
            for (const Warrior &existingWarrior: warriorVector) {
                if (existingWarrior.name == warriorName1) {
                    warrior1Found = true;
                }
                if (existingWarrior.name == warriorName2) {
                    warrior2Found = true;
                }
                // Break the loop early if both warriors are found
                if (warrior1Found && warrior2Found) {
                    break;
                }
            }
            if (warrior1Found && warrior2Found) {
                // Both warriors exist, proceed with the battle
                Warrior warrior1 = searchForWarrior(warriorName1, warriorVector);
                Warrior warrior2 = searchForWarrior(warriorName2, warriorVector);
                warriorBattle(warrior1, warrior2);
                updateWarriorStats(warrior1, warrior2, warriorVector);
            } else {
                // Handle the case where one or both warriors are not found
                if (!warrior1Found && !warrior2Found){
                    cout << "Error: both warriors " << warriorName1 << " and " <<
                    warriorName2 << " are not defined." << endl;
                }
                else if (warrior1Found){
                    cout << "Error: " << warriorName2 << " not defined." << endl;
                }
                else{
                    cout << "Error: " << warriorName1 << " not defined." << endl;
                }
            }
        }
    }
    warriorFile.close();
}

void fileOpener(ifstream& warriorFile){
    // Opens warrior.txt file and checks if the file exists
    warriorFile.clear();
    warriorFile.open("warriors.txt");
    if (!warriorFile) {
        cerr << "File not Found";
        exit(1);
    }
}

void displayWarriorVector(const vector<Warrior>& warriorVector){
    // Iterates through vector that stores warriors and displays their individual attributes
    cout << "There are: " << warriorVector.size() << " warriors" << endl;
    for (const Warrior& currentWarrior : warriorVector)
        cout << "Warrior: " << currentWarrior.name << ", strength: " << currentWarrior.strength << endl;
}

void warriorBattle(Warrior& warrior1, Warrior& warrior2){
    //  Conducts battles between warriors, through comparison of warrior strengths
    //  Updates warrior strengths after battle is fought
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if (warrior1.strength == 0 || warrior2.strength  == 0){  // if one of the warriors have zero strength
        if (warrior1.strength == 0 && warrior2.strength  == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (warrior1.strength  == 0){
            cout << "He's dead, " << warrior2.name << endl;
        }
        else {
            cout << "He's dead, " << warrior1.name << endl;
        }
    }
    else if (warrior1.strength == warrior2.strength){  // if both warriors have the same strength values
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name
                << " die at each other's hands" << endl;
        warrior1.strength = 0;
        warrior2.strength = 0;
    }
    else if (warrior1.strength > warrior2.strength){  // if warrior1 has more strength than warrior2
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    }
    else { // if warrior2 has more strength than warrior1
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.strength-= warrior1.strength;
        warrior1.strength = 0;
    }
}

void updateWarriorStats(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior>& warriorVector){
    // updates warrior stats to the vector that holds all the registered warriors
    for (Warrior& currentWarrior: warriorVector){
        if (currentWarrior.name == warrior1.name){
            currentWarrior = warrior1;
        }6
        else if (currentWarrior.name == warrior2.name){
            currentWarrior = warrior2;
        }
    }
}

Warrior searchForWarrior(const string& name, const vector<Warrior>& warriorVector){
    // checks if a warrior exists, then returns the warrior object if it exists
    for (const Warrior& currentWarrior: warriorVector){
        if (currentWarrior.name == name){
            return currentWarrior;
        }
    }
}

Warrior constructWarrior(const string& name, const int strength){
    // constructs a warrior object and returns it
    Warrior newWarrior(name, strength);
    return newWarrior;
}
