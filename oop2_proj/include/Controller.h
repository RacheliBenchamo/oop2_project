#pragma once
#include <SFML\Graphics.hpp>
#include "ScreensInclude\MenuScreen.h"
#include "ScreensInclude\HelpScreen.h"
#include "ScreensInclude\WinGameScreen.h"
#include "ScreensInclude\WinLevelScreen.h"
#include "ScreensInclude\LoseScreen.h"
#include "ScreensInclude\GameScreen.h"
#include "FileManager.h"
#include <array>

class Controller
{
public:
    Controller();
    ~Controller() {};

    void run();
    void handleScreens(screensOption);
    gender getGenderFromMenu()const;

private:
    void setScreens();

    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<Screen>> m_screens;
};
