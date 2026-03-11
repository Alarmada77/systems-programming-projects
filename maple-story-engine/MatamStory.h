
#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include "Players/Player.h"
#include "Events/Event.h"

using std::vector;
using std::unique_ptr;

class MatamStory{
private:
    unsigned int turnIndex;
    vector<Player> players;
    vector<unique_ptr<Event>> events;
    void parsePlayers(std::istream& playersStream);
    void parseEvents(std::istream& eventsStream);
    void printLeaderBoard() const;
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
