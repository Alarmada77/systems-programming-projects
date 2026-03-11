#include "Player.h"
#include <sstream>

Player::Player(const string &name, int level, int force, const shared_ptr<Job> &job,
  CharacterType character) :
name(name), level(level), force(force), job(job), character(character) {
    currentHP = job->getMaxHP();
    maxHP = job->getMaxHP();
    coins = job->getCoins();
}

string Player::getCharacterString() const {
    switch (character) {
        case CharacterType::Responsible: return "Responsible";
        case CharacterType::RiskTaking: return "RiskTaking";
        default: return "Unknown";
    }
}


string Player::getDescription() const {
    std::ostringstream oss;
    oss << name << ", " << job->getJobName()
        << " with " << getCharacterString()
        << " character (level " << level
        << ", force " << force << ")";
    return oss.str();
}

void Player::heal(int amount) {
    currentHP += amount;
    if (currentHP > maxHP)
        currentHP = maxHP;
    else if (currentHP < 0)
        currentHP = 0;
}

void Player::addCoins(int amount) {
    coins += amount;
    if (coins < 0) {
        coins = 0;
    }
}
