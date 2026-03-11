#include "Job.h"
#include "Player.h"

int Job::getCombatPower(const Player& player) const {
    return player.getForce() + player.getLevel();
}

int Warrior::getCombatPower(const Player& player) const {
    return player.getForce() * 2 + player.getLevel();
}
