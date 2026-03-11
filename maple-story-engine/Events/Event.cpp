#include "../Events/Event.h"

Event::Event() = default;
Event::~Event() = default;

void SolarEclipse::applyOn(Player& player)  {
    int force = player.getForce();
    if (player.getJobName() == "Magician")
        player.setForce(force + 1);
    else player.setForce(force - 1);
}

void PotionsMerchant::applyOn(Player& player) {
    const int price = 5;
    const int healAmount = 10;

    if (player.getCharacterString() == "Responsible") {
        while (player.getCoins() >= price && player.getHealthPoints() < player.getMaxHP()) {
            player.addCoins(-price);
            player.heal(healAmount);
        }
    }
    else if (player.getCharacterString() == "RiskTaking") {
        if (player.getHealthPoints() < 50 && player.getCoins() >= price) {
            player.addCoins(-price);
            player.heal(healAmount);
        }
    }
}
