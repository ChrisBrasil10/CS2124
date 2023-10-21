/*
  hw03.cpp
  September 25, 2023
  Chris Brasil
  Simulate battles between warriors
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class Warrior{
    class Sword;
    //Makes the ostream operator a friend of the Warrior Class and Sword Class.
    friend ostream& operator<< (ostream& os, const Warrior& warrior);
    friend ostream& operator<< (ostream& os, const Warrior::Sword& aSword);

public:
    //Defining Warrior Class Constructor
    Warrior(const string& warriorName, const string& swordName, int swordStrength) :
            warriorName(warriorName), sword(swordName, swordStrength) {}

    // defines the setters and getters of warrior attributes
    const string getname(){return warriorName;}
    int getStrength() {return sword.getSwordStrength();}
    void updateStrength(int newSwordStrength) {sword.updateSwordStrength(newSwordStrength);}

    void battle(Warrior& enemyWarrior){ // defines battle method inside warrior class
        cout << getname() << " battles " << enemyWarrior.getname() << endl;

        if (getStrength() == 0 || enemyWarrior.getStrength() == 0){     // If one or more warriors have no sword strength left
            if (getStrength() == 0 && enemyWarrior.getStrength() == 0) {
                cout << "Oh, NO! They're both dead! YUCK!" << endl;
            }
            else if(enemyWarrior.getStrength() == 0) {
                cout << "He's dead, " << getname() << endl;
            }
            else{
                cout << "He's dead, " << enemyWarrior.getname() << endl;
            }
        }
        else if (getStrength() == enemyWarrior.getStrength()){ // Checks if both warrior swords are the same strength
            cout << "Mutual Annihilation: " << getname() << " and " << enemyWarrior.getname()
                 << " die at eachother's hands" << endl;
            updateStrength(0);  // Makes main warrior sword strength 0
            enemyWarrior.updateStrength(0); // Makes enemy sword strength 0
        }
        else if(getStrength() > enemyWarrior.getStrength()){
            cout << getname() << " defeats " << enemyWarrior.getname() << endl;
            int newStrength = getStrength()- enemyWarrior.getStrength();
            updateStrength(newStrength); // Updates main warrior sword strength to new one.
            enemyWarrior.updateStrength(0); // Makes enemy sword strength 0
        }
        else{
            cout << enemyWarrior.getname() << " defeats " << getname() << endl;
            int newStrength = enemyWarrior.getStrength()-getStrength();
            enemyWarrior.updateStrength(newStrength); // Makes enemy sword strength to new one.
            updateStrength(0); // Makes main warrior sword strength 0
            }
        }

private:
    class Sword{
        friend ostream& operator<< (ostream& os, const Sword& aSword);
        // making ostream operator a friend of the sword class
    public:
        Sword(const string& swordName, int swordStrength) : // Defining Sword Class Constructor
                swordName(swordName), swordStrength(swordStrength){}

        // Creating setters and getters of sword attributes
        const string& getSwordName() const {return swordName;}
        int getSwordStrength() const {return swordStrength;}
        void updateSwordStrength(int newSwordStrength) {swordStrength = newSwordStrength;}

    private:
        string swordName;
        int swordStrength;
    };
    string warriorName;
    Sword sword;
}
;

// Function Prototyping
void displayWarriorStatus(const vector<Warrior>& warriorVector);
int searchForWarrior(const string& warriorName, const vector<Warrior>& warriorVector);

int main() {
    ifstream warriorFile;
    warriorFile.open("warriors.txt"); //Attempts to open warrior file
    if (!warriorFile) {
        cerr << "File not found" << endl;
        return 1; // Return an error code to the operating system if not found
    }

    string command;
    vector<Warrior> warriorVector;

    while (warriorFile >> command) { // Iterates through the warrior file for command words
        if (command == "Warrior") {
            string warriorName, swordName;
            int swordStrength;

            warriorFile >> warriorName >> swordName >> swordStrength; // Retrieves attributes of the warrior
            bool nameTaken = false;
            for (const Warrior& currentWarrior : warriorVector) { //Checks if name of warrior already exists
                if (currentWarrior.getname() == warriorName) {
                    nameTaken = true;
                    break;
                }
            }
            if (nameTaken) {
                cout << "Error: The warrior name " << warriorName << " is already taken" << endl;
            } else {
                warriorVector.emplace_back(warriorName, swordName, swordStrength); // Adds warrior to warrior vector
            }
        } else if (command == "Status") {
            displayWarriorStatus(warriorVector);
        }
        else{
            string firstWarriorName, secondWarriorName;
            warriorFile >> firstWarriorName >> secondWarriorName;

            bool firstWarriorFound = false;
            bool secondWarriorFound = false;

            for (const Warrior& currentWarrior : warriorVector){ // Iterates through warrior vector to see if both warriors exist
                if (currentWarrior.getname() == firstWarriorName){
                    firstWarriorFound = true;
                }
                if (currentWarrior.getname() == secondWarriorName){
                    secondWarriorFound = true;
                }
                if (firstWarriorFound && secondWarriorFound){
                    break;
                }
            }
            if (firstWarriorFound && secondWarriorFound){
                int firstWarriorIndex = searchForWarrior(firstWarriorName, warriorVector); // retrieves index of first warrior
                int secondWarriorIndex = searchForWarrior(secondWarriorName, warriorVector); // retrieves index of second warrior
               warriorVector[firstWarriorIndex].battle(warriorVector[secondWarriorIndex]); // Initiates battle between warriors through the battle method
            }
            else{
                cout << "One or more warriors could not be found" << endl;
            }
        }
    }
    warriorFile.close(); // Closes the warrior file
    return 0;
}

void displayWarriorStatus(const vector<Warrior>& warriorVector) { //displays the amount of warriors and their attributes
    cout << "There are: " << warriorVector.size() << " warriors" << endl;
    for (const Warrior& currentWarrior : warriorVector) {
        cout << currentWarrior;
    }
}

 int searchForWarrior(const string& warriorName, vector<Warrior>& warriorVector){ // Iterates through warrior vector to check for name, returns index within the vector
    for (size_t i = 0; i <warriorVector.size(); i++){
        if (warriorVector[i].getname() == warriorName){
            return i;
        }
    }
    return 0;
}

ostream& operator<< (ostream& os, const Warrior& aWarrior){
    os << "Warrior: " << aWarrior.getname() << "," << aWarrior.sword << endl;
    return os;
}

ostream& operator <<(ostream& os, const Warrior::Sword& aSword){
    os << " weapon: " << aSword.getSwordName() << ", " << aSword.getSwordStrength();
    return os;
}
