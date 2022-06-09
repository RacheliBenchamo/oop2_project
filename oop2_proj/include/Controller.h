#pragma once
#include <SFML\Graphics.hpp>
#include "MenuScreen.h"
#include "HelpScreen.h"
#include "WinScreen.h"
#include "LoseScreen.h"

#include "Board.h"
#include "DataBase.h"
#include "StatusBar.h"
#include "FileManager.h"
#include <array>

class Controller
{
public:
    Controller();
    ~Controller() {};
    void run();

private:
    void handelEvents();
    void setView();
    void setNewGame();
    void handelMouseButtonReleased(sf::Event);
    void handelMusicButtonReleased();
    void handelStopPlayButtonReleased();
    void resetLevel();
    void startNewLevel();
    void startnewGame();
    void winGameScreen();
    void winLevelScreen();
    void setWinScreen(backgroundsType, sounds);
    void setBackground();
    void setViewToCenter();
    void setBigView();
    void setScreens();
    void handleScreens();


    void startSound();

    sf::RenderWindow m_window;
    StatusBar m_statusBar;
    Board m_board;
    DataBase  m_dataBase;
    sf::Clock m_gameClock;
    sf::Sound m_backGroundMusic;
    int m_levelNum = 1;
    sf::RectangleShape m_currLevelBackground;
    sf::View m_view;
    bool m_playButton;
    std::vector<std::unique_ptr<Screen>> m_screens;
    screensOption currScreen= NONE;
    gender m_playerGender = MALE;
};
