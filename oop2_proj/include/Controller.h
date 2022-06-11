#pragma once
#include <SFML\Graphics.hpp>
#include "MenuScreen.h"
#include "HelpScreen.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include "GameScreen.h"
#include "FileManager.h"
#include <array>

class Controller
{
public:
    Controller();
    ~Controller() {};

    void run();
    void handleScreens(screensOption);
    gender getGenderFromMenu();
    bool getResetLevelFromLoseScreen()const { return m_toReset; };

private:
    void setScreens();

    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<Screen>> m_screens;
    bool m_toReset = false;
};
