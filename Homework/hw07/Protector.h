#ifndef UNTITLED1_PROTECTOR_H
#define UNTITLED1_PROTECTOR_H

#include <fstream>
#include <iostream>
#include <string>

namespace WarriorCraft {

    class Lord;

    class Protector {
        friend std::ostream& operator<<(std::ostream& os, const Protector& aProtector);
    public:
        // constructor
        Protector(const std::string& aName, double theStrength);

        // getters and setters
        const std::string& getName() const;
        double getStrength() const;
        void setStrength(double theStrength);
        void setLord(Lord* lordPtr);
        Lord* getLord() const;

        // Protector runaway
        bool runaway();

        // pure virtual defend method
        virtual void defend() const = 0;

    private:
        // private variables of Protector class
        std::string name;
        double strength;
        Lord* lord;
    };  // class Protector

    class Warrior : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };  // class Warrior

    class Wizard : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };  // class Wizard

    class Archer : public Warrior {
    public:
        using Warrior::Warrior;
        void defend() const override;
    };  // class Archer

    class Swordsman : public Warrior {
    public:
        using Warrior::Warrior;
        void defend() const override;
    };  // class Swordsmen
}

#endif //UNTITLED1_PROTECTOR_H
