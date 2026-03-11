#pragma once
#include "../Players/Job.h"
#include <string>
#include <memory>

using std::shared_ptr;
using std::string;

enum class CharacterType { Responsible, RiskTaking };

class Player {
  string name;
 int level;
 int force;
 int currentHP;
 int maxHP;
 int coins;
 shared_ptr<Job> job;
 CharacterType character;
public:

 Player(const string &name, int level, int force, const shared_ptr<Job> &job,
  CharacterType character);
 /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const{return name;}

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const{return level;}
    void levelUp(){level++;}

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const{return force;}
    void setForce(int newForce){force = newForce;}

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const{return currentHP;}
    void heal(int amount);

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const{return coins;}
    void addCoins(int amount);

    int getMaxHP() const{return maxHP;}

    shared_ptr<Job> getJob() const{return job;}
    string getCharacterString() const;

    int getCombatPower() const {return job->getCombatPower(*this);}

 string getJobName() const { return job->getJobName(); }
};
