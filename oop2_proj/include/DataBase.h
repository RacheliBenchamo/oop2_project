#pragma once
#include "GameObjBase.h"
#include "StaticInclude\Teleport.h"
#include "StaticInclude\Diamond.h"
#include "StaticInclude\Rope.h"
#include "StaticInclude\Floor.h"
#include "StaticInclude\LeftFloor.h"
#include "StaticInclude\RightFloor.h"
#include "StaticInclude\Gate.h"
#include "StaticInclude\Potion.h"
#include "StaticInclude\LifePosion.h"
#include "StaticInclude\PowerPosion.h"
#include "StaticInclude\StageDec.h"
#include "MovingInclude\Player.h"
#include "MovingInclude\Monster.h"

#include "CollisionDetection.h"


class DataBase
{
public:
    DataBase();
    ~DataBase() {};

    void draw(sf::RenderWindow&);
    void move(const sf::Time);
    void eraseObj();

    void setLevelSize(const int,const int);
    sf::Vector2f getLevelSize()const { return m_levelSize; }
    void setLevelMaxDiamonds(const int max) { m_currLevelMaxDiamonds= max; }
    int getLevelMaxDiamonds()const { return m_currLevelMaxDiamonds; }
    void setData(const char, const int, const int);
    void FindTeleportPartner() const;
    bool winLevel()const;
    bool loseLevel() const{ return getPlayerLife() <= 0; };
    sf::Vector2f getPlayerPos() const { return m_player->getPos(); }
    int getPlayerPower()const  { return m_player->getPower(); }
    int getPlayerLife()const { return m_player->getLife(); }
    int getPlayerDiamonds()const { return m_player->getDiamondsCount(); }
    void setGender(const gender g) { m_gender = g; };
    void resetLevel() { m_currLevel = 1; };
    void setCurrLevel(const int currLevel) { m_currLevel = currLevel; };
    void printDamage();
    
private:
    bool createStaticObj(const char , const sf::Vector2f&);
    void createMovingObj(const char , const sf::Vector2f&);
    void replaceMonsterWithPotion();

    void drawStaticObj(sf::RenderWindow& );
    void drawMovingObj(sf::RenderWindow& );
    void handelCollisions();
    void handelMovingCollisions();
    void handelTeleportCollisions();
    void handelPlayerStuff(const sf::Time);
    void AllowedToEnterTeleport(const int, const int);
    void deleteRelevantObj();
    void randPotion(const sf::Vector2f pos);
    void eraseAllMonsters();

    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<StaticObj>> m_staticsObj;
    std::vector<std::unique_ptr<Monster>> m_monsters;
    std::vector<std::unique_ptr<Teleport>> m_teleport;
    std::vector<std::unique_ptr<Rope>> m_rope;

    sf::Vector2f m_levelSize;
    int m_currTeleport;
    int m_currLevelMaxDiamonds = 0;
    sf::Clock m_clock;
    int m_currLevel;
    gender m_gender = MALE;
};

