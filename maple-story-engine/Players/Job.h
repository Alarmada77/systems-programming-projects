#pragma once
#include <string>

using std::string;

class Player;

class Job {
public:
    virtual ~Job() = default;
    virtual int getCombatPower(const Player& player) const;
    virtual int getMaxHP() const { return 100; }
    virtual int getCoins() const { return 10; }
    virtual string getJobName() const = 0;
};

class Warrior : public Job {
public:
    int getCombatPower(const Player& player) const override;
    int getMaxHP() const override { return 150; }
    string getJobName() const override { return "Warrior"; }
};

class Archer : public Job {
public:
    int getCoins() const override { return 20; }
    string getJobName() const override { return "Archer"; }
};

class Magician : public Job {
public:
    string getJobName() const override { return "Magician"; }
};
