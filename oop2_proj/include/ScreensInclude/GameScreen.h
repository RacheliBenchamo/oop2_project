#pragma once
#include <SFML\Graphics.hpp>
#include "Controller.h"

#include "Board.h"
#include "DataBase.h"
#include "StatusBar.h"
#include "FileManager.h"
#include <array>

class GameScreen :public Screen
{
public:
    GameScreen(sf::RenderWindow& ,Controller*);
    ~GameScreen() {};
    screensOption activateScreen(sf::RenderWindow&)override;

private:
    virtual screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)
    {return NONE;};
    virtual void handleMove(const sf::Vector2f&) {};
    virtual void draw(sf::RenderWindow& window) {};


    void handelEvents();
    void setView();
    void setNewGame();
    void handelMouseButtonReleased(sf::Event);
    void handelMusicButtonReleased();
    void handelStopPlayButtonReleased();
    void resetLevel();
    void startNewLevel();
    void startnewGame();
    void setBackground();
    void setViewToCenter();
    void setBigView();
    void startSound();

    sf::RenderWindow* m_window;
    StatusBar m_statusBar;
    Board m_board;
    DataBase  m_dataBase;
    sf::Clock m_gameClock;
    sf::Sound m_backGroundMusic;
    int m_levelNum = 1;
    sf::RectangleShape m_currLevelBackground;
    sf::View m_view;
    bool m_playButton;

    gender m_playerGender = MALE;
    Controller* m_controller;

};
