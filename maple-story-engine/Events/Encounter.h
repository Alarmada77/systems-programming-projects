#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Event.h"

using std::vector;
using std::unique_ptr;
using std::string;

class Encounter : public Event {
protected:
    int combatPower;
    int loot;
    int damage;

public:
    Encounter(int combatPower, int loot, int damage)
        : combatPower(combatPower), loot(loot), damage(damage) {}
    virtual ~Encounter() = default;

    virtual int getCombatPower() const { return combatPower; }
    virtual int getLoot() const { return loot; }
    virtual int getDamage() const { return damage; }
    string getDescription() const override = 0;
    void applyOn(Player& player) override;
};

class Snail : public Encounter {
public:
    Snail() : Encounter(5, 2, 10) {}
    string getDescription() const override {
        return "Snail (power 5, loot 2, damage 10)";
    }
};

class Slime : public Encounter {
public:
    Slime() : Encounter(12, 5, 25) {}
    string getDescription() const override {
        return "Slime (power 12, loot 5, damage 25)";
    }
};

class Balrog : public Encounter {
public:
    Balrog() : Encounter(15, 100, 9001) {}
    void increasePower(int delta = 2) { combatPower += delta; }
    void applyOn(Player& player) override;
    string getDescription() const override {
        return "Balrog (power " + std::to_string(combatPower) +
               ", loot 100, damage 9001)";
    }
};

class Pack : public Encounter {
    vector<unique_ptr<Encounter>> encounters;

public:
    Pack(vector<unique_ptr<Encounter>> encounters);
    void applyOn(Player& player) override;
    int getCombatPower() const override;
    int getLoot() const override;
    int getDamage() const override;
    string getDescription() const override;
    const vector<unique_ptr<Encounter>>& getMembers() const { return encounters; }
};
