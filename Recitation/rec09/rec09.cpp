/*
  Chris Brasil
  11/10/2023
  rec10_start.cpp
  Starting code 23S
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Instrument{
    friend ostream& operator<<(ostream& os, const Instrument& anInstrument){
        anInstrument.display(os);
        return os;
    }
public:
    virtual void makeSound() const = 0;
    virtual void display(ostream&) const = 0;
    virtual void play() const = 0;
};
void Instrument::makeSound() const { cout << "To make sound... " ; }

class Brass: public Instrument{
public:
    Brass(unsigned mouthPiece):mouthPiece(mouthPiece){}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthPiece << endl;
    }
protected:
    unsigned getMouthPiece() const {return mouthPiece;}
private:
    unsigned mouthPiece;
};



class Trombone: public Brass{
public:
    Trombone(unsigned mouthPiece) : Brass(mouthPiece) {}
    void display(ostream& os) const {os << "Trombone: " << getMouthPiece();}
    void play() const override {cout << "Blat";}
};

class Trumpet: public Brass{
public:
    Trumpet(unsigned mouthPiece) : Brass(mouthPiece) {}
    void display(ostream& os) const {os << "Trumpet: " << getMouthPiece();}
    void play() const override {cout << "Toot";}
};

class String: public Instrument{
public:
    String(unsigned pitch) : pitch(pitch){}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
protected:
    unsigned getPitch() const {return pitch;}

private:
    unsigned pitch;
};

class Violin: public String{
public:
    Violin(unsigned pitch) : String(pitch) {}
    void display(ostream& os) const {os << "Violin: " << getPitch();}
    void play() const override {cout << "Screech";}
};

class Cello: public String {
public:
    Cello(unsigned pitch) : String(pitch) {}
    void display(ostream& os) const {os << "Cello: " << getPitch();}
    void play() const override {cout << "Squawk";}
};
class Percussion: public Instrument{
    void makeSound() const override{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum: public Percussion{
public:
    Drum():Percussion(){}
    void display(ostream& os) const{os << "Drum";}
    void play() const override {cout << "Boom";}

};

class Cymbal: public Percussion{
public:
    Cymbal():Percussion(){}
    void display(ostream& os) const{os << "Cymbal";}
    void play() const override {cout << "Crash";}
};

class MILL{
    friend ostream& operator<<(ostream& os, const MILL& aMill) {
        os << "The MILL has the following instruments: ";
        bool check = false;
        for (const Instrument* currPtr : aMill.instrVector) {
            if (currPtr) {
                check = true;
                os << "\n\t" << *currPtr;  // Output the content of the instrument using the << operator
            }
        }
        if (!check) {
            os << "None";
        }

        return os;
    }
public:
    void receiveInstr(Instrument& anInstrument) {
        anInstrument.makeSound();
        for (size_t i = 0; i < instrVector.size(); ++i) {
            if (instrVector[i] == nullptr) {
                instrVector[i] = &anInstrument;
                return;
            }
        }
        instrVector.push_back(&anInstrument);
    }

    void dailyTestPlay() {
        for (size_t i = 0; i < instrVector.size(); ++i) {
            const Instrument* instrPtr = instrVector[i];
            if (instrPtr) {
                instrPtr->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < instrVector.size(); ++i) {
            Instrument*& currInstr = instrVector[i];
            if (currInstr) {
                Instrument* instrLend = currInstr;
                currInstr = nullptr;
                return instrLend;
            }
        }
        return nullptr;
    }

private:
    vector<Instrument*> instrVector;
};


class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cout << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& member) { members.push_back(&member); }
    void play() const {
        for (Musician* member : members) {
            member->play();
        }
        cout << endl;
    }

private:
    vector<Musician*> members;
};
// PART TWO


int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();     // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
