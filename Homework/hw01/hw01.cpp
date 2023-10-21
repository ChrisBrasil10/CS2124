/*
  hw01.cpp
  September 12, 2023
  Chris Brasil
  Decrypts texts encrypted with classic Caesar cypher algorithm
*/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

char shiftCharacter(char letter, int shift);
void modifyFunc(string &line, int rotation);

int main(){
    ifstream encrypted;
    encrypted.open("encrypted.txt");
    if (!encrypted){
        cerr << "Failed to open encrypted.txt" << endl;
        exit(1);
    }
    int value;
    encrypted >> value;
    string line;
    vector<string> lineVector;
    while (getline(encrypted, line)){
        modifyFunc(line, value);
        lineVector.push_back(line);
    }
    encrypted.close();
    for (int i = lineVector.size() - 1; i >= 0; --i){
        cout << lineVector[i] << endl;
    }
    return 0;
}

char shiftCharacter (char letter, int shift) {
    if (65 <= letter && letter <= 90) {
        letter -= shift;
        if (letter < 65) {
            int cycleVal = 65 - letter;
            letter = 91 - cycleVal;
        } else if (letter > 90) {
            int cycleVal = letter - 90;
            letter = 64 + cycleVal;
        }
    }
    return letter;
}

void modifyFunc(string &line, int rotation){
    for(int i = 0; i < line.size(); i++){
        char newLetter = shiftCharacter(line[i], rotation);
        line[i] = newLetter;
    }
}
