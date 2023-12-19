#ifndef UNTITLED1_NOBLE_H
#define UNTITLED1_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Protector;

    // Simulate the behavior of Noble
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& aNoble);
    public:
        // constructor
        Noble(const std::string& theName);

        // getters and setters
        const std::string& getName() const;

        void battle(Noble& enemy);  // Battle between Nobles
        void die();  // change the status of "alive" and set strength to 0

        // pure virtual methods
        virtual double getStrength() const = 0;
        // if the instance is a Lord, update strength of every Protector
        // if it is a PersonWithStrengthToFight, update itself's strength
        virtual void updateStrength(double winnerStrength,
                                    double loserStrength) = 0;
        // if the instance is a Lord, call defend() for every Protector
        // if it is a PersonWithStrengthToFight, output "Ugh!"
        virtual void defend() const = 0;

        virtual void display(std::ostream& os) const = 0;

    protected:  // protected getter and setter
        void changeAliveStatus();
        bool getAliveStatus() const;

    private:  // variables of Noble class
        std::string name;
        bool alive;
    };  // class Noble

    class Lord : public Noble {
    public:
        Lord(const std::string& aName);  // constructor

        double getStrength() const override;
        // multiply strength of each protector with the ratio
        void updateStrength(double winnerStrength, double loserStrength) override;
        void defend() const override;  // call defend() for every Protector
        // hire/fire a protector
        bool hires(Protector& aProtector);
        bool fires(Protector& aProtector);
        // attempt to remove a protector (fire/runaway)
        bool remove(Protector& aProtector);
        void display(std::ostream& os) const ;

    private:  // variables of Lord class
        std::vector<Protector*> army;
    };  // class Lord

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& aName,
                                  double theStrength);  // constructor

        // getter and setter
        double getStrength() const override;
        void updateStrength(double winnerStrength, double loserStrength) override;
        void display(std::ostream& os) const;
        void defend() const override;

    private:  // variables of PersonWithStrengthToFight class
        double strength;
    };  // class PersonWithStrengthToFight
}

#endif //UNTITLED1_NOBLE_H
