#pragma once
#include <SFML\Graphics.hpp>
#include "StatusBar.h"
#include "FileManager.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include <GameObjBase.h>
#include "StaticInclude\Teleport.h"
#include "StaticInclude\Diamond.h"
#include "StaticInclude\Floor.h"
#include "StaticInclude\Gate.h"
#include "StaticInclude\Posion.h"
#include "StaticInclude\LifePosion.h"
#include "StaticInclude\PowerPosion.h"
#include "StaticInclude\StageDec.h"
#include "StaticInclude\Floor.h"
#include "MovingInclude\Player.h"
#include "MovingInclude\Monster.h"

#include "CollisionDetection.h"



#include <array>


class DataBase
{
public:
    DataBase();
    ~DataBase() {};

    void setLevelSize(int, int);
    void setLevelMaxDiamonds(int max) { m_currLevelMaxDiamonds= max; }
    const int getLevelMaxDiamonds() { return m_currLevelMaxDiamonds; }
    void setData(char, int, int);
    void draw(sf::RenderWindow&);
    void FindTeleportPartner() const;
    void move(sf::Time);
   // bool takeCurrGift(giftType g) { return m_takeGifts[g]; }
    bool winLevel();
    void eraseObj();
    sf::Vector2f getPlayerPos() const { return m_player->getPos(); }
    int getPlayerPower()const  { return m_player->getPower(); }
    int getPlayerLife()const { return m_player->getLife(); }
    int getPlayerDiamonds()const { return m_player->getDiamondsCount(); }

    void setCurrLevel(int currLevel) { m_currLevel = currLevel;};

private:
    bool createStaticObj(const char , const sf::Vector2f&);
    void createMovingObj(const char , const sf::Vector2f&);
    void replaceMonsterWithPotion();
   /* template<class T>
    void drowObj();*/

    void drawStaticObj(sf::RenderWindow& );
    void drawMovingObj(sf::RenderWindow& );
    void handelCollisions();
    bool handelPlayerCollisions();
    void handelTeleportCollisions();
    void handelPlayerStuff(sf::Time);
    void itsAllowedToEnterTheTeleport(int, int);
    bool ThereIsNoObjectOnTheMemberTel(int);
   //void handelMonstersCollisions();
    void deleteRelevantObj();
    void grillPotion(sf::Vector2f pos);
    void takeGift();
    void resetTakeGifts();
    void eraseAllMonsters();

    sf::Vector2f m_levelSize;
    sf::RenderWindow m_window;
    StatusBar m_statusBar;
    bool m_takeGifts[NUM_OF_GIFT_TYPES];
    bool m_GiftsWithTime;
    int m_currTeleport;

    sf::RectangleShape m_movingRec;
    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<StaticObj>> m_staticsObj;
    std::vector<std::unique_ptr<Monster>> m_monsters;
    std::vector<std::unique_ptr<Teleport>> m_teleport;
    std::vector<std::unique_ptr<Floor>> m_floor;

    int m_currLevelMaxDiamonds = 0;
    sf::Clock m_clock;
    int m_currLevel;
};

