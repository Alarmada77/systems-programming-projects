#include "MatamStory.h"
#include "Events/Encounter.h"
#include "Events/Event.h"
#include "Players/Job.h"
#include "Utilities.h"
#include <sstream>
#include <algorithm>


void MatamStory::parsePlayers(std::istream& playersStream)
{
    std::string name, jobName, characterName;
    while (playersStream >> name >> jobName >> characterName) {

        std::shared_ptr<Job> job;
        if (jobName == "Warrior")      job = std::make_shared<Warrior>();
        else if (jobName == "Archer")  job = std::make_shared<Archer>();
        else if (jobName == "Magician") job = std::make_shared<Magician>();
        else throw std::invalid_argument("Invalid Players File");

        CharacterType character;
        if (characterName == "Responsible") character = CharacterType::Responsible;
        else if (characterName == "RiskTaking") character = CharacterType::RiskTaking;
        else throw std::invalid_argument("Invalid Players File");

        if (name.length() < 1 || name.length() > 15)
            throw std::invalid_argument("Invalid Players File");

        players.emplace_back(name, 1, 5, job, character);
    }

    if (players.size() < 2 || players.size() > 6)
        throw std::invalid_argument("Invalid Players File");
}

void MatamStory::parseEvents(std::istream& eventsStream)
{
    std::string word;
    while (eventsStream >> word) {
        if (word == "SolarEclipse") {
            events.push_back(std::make_unique<SolarEclipse>());
        }
        else if (word == "PotionsMerchant") {
            events.push_back(std::make_unique<PotionsMerchant>());
        }
        else if (word == "Snail") {
            events.push_back(std::make_unique<Snail>());
        }
        else if (word == "Slime") {
            events.push_back(std::make_unique<Slime>());
        }
        else if (word == "Balrog") {
            events.push_back(std::make_unique<Balrog>());
        }
        else if (word == "Pack") {
            int packSize;
            if (!(eventsStream >> packSize) || packSize <= 0)
                throw std::invalid_argument("Invalid Events File");

            std::vector<std::unique_ptr<Encounter>> members;
            for (int i = 0; i < packSize; ++i) {
                std::string monster;
                if (!(eventsStream >> monster))
                    throw std::invalid_argument("Invalid Events File");

                if (monster == "Snail") members.push_back(std::make_unique<Snail>());
                else if (monster == "Slime") members.push_back(std::make_unique<Slime>());
                else if (monster == "Balrog") members.push_back(std::make_unique<Balrog>());
                else throw std::invalid_argument("Invalid Events File");
            }

            events.push_back(std::make_unique<Pack>(std::move(members)));
        }
        else throw std::invalid_argument("Invalid Events File");
    }

    if (events.empty())
        throw std::invalid_argument("Invalid Events File");
}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream)
{
    parsePlayers(playersStream);
    parseEvents(eventsStream);
    turnIndex = 0;
}



void MatamStory::playTurn(Player& player)
{
    if (player.getHealthPoints() <= 0)
        return;

    unsigned int eventIndex = turnIndex % events.size();
    Event& event = *events[eventIndex];

    printTurnDetails(turnIndex + 1, player, event);

    std::string outcome;

    if (auto encounter = dynamic_cast<Encounter*>(&event)) {
        int beforeHP = player.getHealthPoints();
        int beforeLevel = player.getLevel();

        encounter->applyOn(player);

        if (player.getLevel() > beforeLevel)
            outcome = getEncounterWonMessage(player, encounter->getLoot());
        else if (player.getHealthPoints() < beforeHP)
            outcome = getEncounterLostMessage(player, encounter->getDamage());
    }
    else if (auto solar = dynamic_cast<SolarEclipse*>(&event)) {
        int beforeForce = player.getForce();
        solar->applyOn(player);
        int effect = player.getForce() - beforeForce;
        outcome = getSolarEclipseMessage(player, effect);
    }
    else if (auto merchant = dynamic_cast<PotionsMerchant*>(&event)) {
        int beforeHP = player.getHealthPoints();
        merchant->applyOn(player);
        int potionsBought = (player.getHealthPoints() - beforeHP) / 10;
        if (potionsBought < 0) potionsBought = 0;
        outcome = getPotionsPurchaseMessage(player, potionsBought);
    }

    printTurnOutcome(outcome);
    turnIndex++;
}



void MatamStory::printLeaderBoard() const
{
    std::vector<Player> sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player& a, const Player& b) {
        if (a.getLevel() != b.getLevel())
            return a.getLevel() > b.getLevel();
        if (a.getCoins() != b.getCoins())
            return a.getCoins() > b.getCoins();
        return a.getName() < b.getName();
    });


    printLeaderBoardMessage();
    int rank = 1;
    for (const auto& player : sortedPlayers)
        printLeaderBoardEntry(rank++, player);
}


void MatamStory::playRound() {

    printRoundStart();

    for (auto& player : players)
        playTurn(player);

    printRoundEnd();


    printLeaderBoard();

    printBarrier();
}

bool MatamStory::isGameOver() const
{
    for (const auto& player : players)
        if (player.getHealthPoints() > 0)
            return false;
    return true;
}


void MatamStory::play()
{
    printStartMessage();
    for (unsigned int i = 0; i < players.size(); ++i)
        printStartPlayerEntry(i + 1, players[i]);

    printBarrier();

    while (!isGameOver())
        playRound();

    printGameOver();

    std::vector<Player> alivePlayers;
    for (const auto& player : players)
        if (player.getHealthPoints() > 0)
            alivePlayers.push_back(player);

    if (alivePlayers.empty())
        printNoWinners();
    else {
        std::sort(alivePlayers.begin(), alivePlayers.end(), [](const Player& a, const Player& b) {
            if (a.getLevel() != b.getLevel()) return a.getLevel() > b.getLevel();
            if (a.getCoins() != b.getCoins()) return a.getCoins() > b.getCoins();
            return a.getName() < b.getName();
        });
        printWinner(alivePlayers.front());
    }
}

