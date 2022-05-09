#pragma once
#include <SFML\Graphics.hpp>
#include "menu.h"
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
    void setNewGame();
    void handelMouseButtonReleased(sf::Event);
    void handelMusicButtonReleased();
    void handelStopPlayButtonReleased();
    void resetLevel();
    void takeBackToPrevLevel();
    void startNewLevel();
    void startnewGame();
    void winGameScreen();
    void winLevelScreen();
    void setWinScreen(backgroundsType, sounds);
    void checkOutGiftTaken();


    sf::RenderWindow m_window;
    StatusBar m_statusBar;
    Menu m_menu;
    Board m_board;
    DataBase  m_dataBase;
    sf::Clock m_gameClock;
    sf::Sound m_backGroundMusic;
    sf::RectangleShape m_background;
    bool m_playButton;


};
