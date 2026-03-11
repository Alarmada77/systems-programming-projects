#include "Encounter.h"
#include <sstream>

Pack::Pack(vector<unique_ptr<Encounter>> encounters)
    : Encounter(0, 0, 0), encounters(std::move(encounters)) {}

int Pack::getCombatPower() const {
    int totalPower = 0;
    for (const auto& e : encounters)
        totalPower += e->getCombatPower();
    return totalPower;
}

int Pack::getLoot() const {
    int totalLoot = 0;
    for (const auto& e : encounters)
        totalLoot += e->getLoot();
    return totalLoot;
}

int Pack::getDamage() const {
    int totalDamage = 0;
    for (const auto& e : encounters)
        totalDamage += e->getDamage();
    return totalDamage;
}

string Pack::getDescription() const {
    std::ostringstream oss;
    oss << "Pack of " << encounters.size()
        << " members (power " << getCombatPower()
        << ", loot " << getLoot()
        << ", damage " << getDamage() << ")";
    return oss.str();
}
void Encounter::applyOn(Player& player) {
    if (player.getCombatPower() >  this->getCombatPower()) {
        player.levelUp();
        player.addCoins(this->loot);
    }else player.heal(this->damage * (-1) );
    if (player.getJobName() == "Warrior")
        player.heal(-10 );
}
void Balrog::applyOn(Player& player) {
    Encounter::applyOn(player);
    this->combatPower += 2;
}

void Pack::applyOn(Player& player) {
    int power = getCombatPower();
    int totalLoot = getLoot();
    int totalDamage = getDamage();

    if (player.getCombatPower() > power) {
        player.levelUp();
        player.addCoins(totalLoot);
    } else {
        player.heal(-totalDamage);
    }

    if (player.getJobName() == "Warrior") {
        player.heal(-10);
    }
}
