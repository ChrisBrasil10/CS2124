/*
    Chris Brasil
    rec02.cpp
    September 15, 2023
    Simulates the Matching of DNA Sequences
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

struct Formula {
    vector<string> names;
    int carbonCount;
    int hydrogenCount;
};

void openFile(ifstream& file);
void fillVector(vector<Formula>& formulas, ifstream& file);
void insertFormula(vector<Formula>& formulas, const string& formula, const string& name);
int findFormulaIndex(const vector<Formula>& formulas, const string& formula);
void displayFormulas(const vector<Formula>& formulas);
void sortFormulas(vector<Formula>& formulas);
void displaySingleFormula(const Formula& formula);

int main() {
    ifstream inputFile;
    openFile(inputFile);

    vector<Formula> formulas;
    fillVector(formulas, inputFile);

    cout << "Unsorted:" << endl;
    displayFormulas(formulas);

    sortFormulas(formulas);

    cout << "\nSorted:" << endl;
    displayFormulas(formulas);

    return 0;
}

void openFile(ifstream& file) {
    string fileName;
    while (true) {
        cout << "File name? ";
        cin >> fileName;
        file.open(fileName);
        if (file.is_open()) {
            break;
        } else {
            cerr << "Failed to open file, try again." << endl;
            file.clear();
        }
    }
}

void fillVector(vector<Formula>& formulas, ifstream& file) {
    string name, formula;
    while (file >> name >> formula) {
        int carbonCount = stoi(formula.substr(1, formula.find('H') - 1));
        int hydrogenCount = stoi(formula.substr(formula.find('H') + 1));

        int index = findFormulaIndex(formulas, formula);
        if (index == -1) {
            Formula newFormula;
            newFormula.carbonCount = carbonCount;
            newFormula.hydrogenCount = hydrogenCount;
            newFormula.names.push_back(name);
            formulas.push_back(newFormula);
        } else {
            formulas[index].names.push_back(name);
        }
    }
}

void insertFormula(vector<Formula>& formulas, const string& formula, const string& name) {
    int carbonCount = 0;
    int hydrogenCount = 0;

    bool parsingCarbon = false;
    for (char c : formula) {
        if (c == 'C') {
            parsingCarbon = true;
        } else if (c == 'H') {
            parsingCarbon = false;
        } else if (isdigit(c)) {
            if (parsingCarbon) {
                carbonCount = carbonCount * 10 + (c - '0');
            } else {
                hydrogenCount = hydrogenCount * 10 + (c - '0');
            }
        }
    }

    int index = findFormulaIndex(formulas, formula);

    if (index == -1) {
        Formula newFormula;
        newFormula.carbonCount = carbonCount;
        newFormula.hydrogenCount = hydrogenCount;
        newFormula.names.push_back(name);
        formulas.push_back(newFormula);
    } else {
        formulas[index].names.push_back(name);
    }
}

int findFormulaIndex(const vector<Formula>& formulas, const string& formula) {
    int carbonCount = 0;
    int hydrogenCount = 0;

    bool parsingCarbon = false;
    for (char c : formula) {
        if (c == 'C') {
            parsingCarbon = true;
        } else if (c == 'H') {
            parsingCarbon = false;
        } else if (isdigit(c)) {
            if (parsingCarbon) {
                carbonCount = carbonCount * 10 + (c - '0');
            } else {
                hydrogenCount = hydrogenCount * 10 + (c - '0');
            }
        }
    }
    for (int i = 0; i < formulas.size(); ++i) {
        if (formulas[i].carbonCount == carbonCount && formulas[i].hydrogenCount == hydrogenCount) {
            return i;
        }
    }
    return -1;
}

void displayFormulas(const std::vector<Formula>& formulas) {
    for (const Formula& f : formulas) {
        cout <<  "C" << f.carbonCount << "H" << f.hydrogenCount << " ";
        for (const string& name : f.names) {
            cout << name << ' ';
        }
        cout << endl;
    }
}

void sortFormulas(std::vector<Formula>& formulas) {
    bool done = false;
    while (!done) {
        done = true;
        for (size_t j = 0; j < formulas.size() - 1; j++) {
            if (formulas[j + 1].carbonCount < formulas[j].carbonCount ||
                (formulas[j + 1].carbonCount == formulas[j].carbonCount &&
                 formulas[j + 1].hydrogenCount < formulas[j].hydrogenCount)) {
                swap(formulas[j + 1], formulas[j]);
                done = false;
            }
        }
    }
}

void displaySingleFormula(const Formula& formula) {
    cout << "C" << formula.carbonCount << "H" << formula.hydrogenCount << " ";
    for (const string& name : formula.names) {
        cout << name << ' ';
    }
    cout << endl;
}
