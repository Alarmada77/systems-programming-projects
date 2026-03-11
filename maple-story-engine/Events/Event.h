
#pragma once

#include "../Players/Player.h"

class Event {
public:
    Event();
    virtual ~Event();
    virtual string getDescription() const = 0;
    virtual void applyOn(Player& player) = 0;
};

class SolarEclipse : public Event {
public:
    string getDescription() const override { return "SolarEclipse"; }
    void applyOn(Player& player) override;
};

class PotionsMerchant : public Event {
public:
    string getDescription() const override { return "PotionsMerchant"; }
    void applyOn(Player& player) override;
};