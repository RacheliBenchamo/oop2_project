#pragma once
#include <SFML\Graphics.hpp>
#include "StatusBar.h"
#include "FileManager.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include <GameObjBase.h>
#include "StaticInclude\Teleport.h"
#include "StaticInclude\Gate.h"
#include "StaticInclude\Gift.h"
#include <array>


class DataBase
{
public:
    DataBase();
    ~DataBase() {};

    void setLevelSize(int, int);
    void setData(char, int, int);
    void draw(sf::RenderWindow& );
    void FindTeleportPartner() const;
    void switchPlayer();
    void move(sf::Time);
    bool takeCurrGift(giftType g) { return m_takeGifts[g]; }
    bool winLevel();
    void eraseObj();
    icons getCurrPlayer()const { return m_currPlayer; }
    void setCurrPlayer(icons currPlayer) { m_currPlayer = currPlayer; }
    void setGiftsWithTime(bool b) { m_GiftsWithTime = b; }

private:
    bool createStaticObj(const char , const size_t ,
        const size_t );
    void createMovingObj(const char , const size_t ,
        const size_t );
    void drawStaticObj(sf::RenderWindow& );
    void drawMovingObj(sf::RenderWindow& );
    void handelCollisions();
    void handelPlayerCollisions();
    void handelTeleportCollisions();
    void itsAllowedToEnterTheTeleport(int, int);
    bool ThereIsNoObjectOnTheMemberTel(int);
    void handelFairiesCollisions();
    void deleteRelevantObj();
    void replaceOrkWithKey();
    std::unique_ptr<Gift>  grillGiftType(icons, int, int);
    void takeGift();
    void resetTakeGifts();
    void eraseAllFairies();

    sf::Vector2f m_levelSize;
    sf::RenderWindow m_window;
    StatusBar m_statusBar;
    bool m_takeGifts[NUM_OF_GIFT_TYPES];
    bool m_GiftsWithTime;
    int m_currTeleport;
    icons m_currPlayer;
    sf::RectangleShape m_movingRec;
    std::array<std::unique_ptr< Player>, NUM_OF_PLAYERS>m_players;
    std::vector<std::unique_ptr<StaticObj> > m_staticsObj;
    std::vector<std::unique_ptr<Fairy>> m_fairies;
    std::vector<std::unique_ptr<Teleport>> m_teleport;
};
