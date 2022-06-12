#include "Controller.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

Controller::Controller()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"The Diamonds Fighter!")
{
	m_window.setFramerateLimit(60);
	setScreens();
}


void Controller::run() try
{
	handleScreens(START);
}

 catch (const std::exception& e) 
 {
	std::cout << e.what();
}
//-----------------------------------------------------------

void Controller::setScreens()
{
	m_screens.push_back(std::make_unique<GameScreen>(m_window,this));
	m_screens.push_back(std::make_unique<HelpScreen>());
	m_screens.push_back(std::make_unique<MenuScreen>()); 
	m_screens.push_back(std::make_unique<LoseScreen>());
	m_screens.push_back(std::make_unique<WinGameScreen>());
	m_screens.push_back(std::make_unique<WinLevelScreen>());

}
//-----------------------------------------------------------
void Controller::handleScreens(screensOption currScreen)
{
	while (currScreen != NONE)
	{
		screensOption scr = m_screens[currScreen]->activateScreen(m_window);
		switch (scr)
		{
		case HELP:
			currScreen = HELP;
			break;
		case MENU:
			currScreen = MENU;
			break;
		default:
			currScreen = NONE;
			break;
		}
	}
}

gender Controller::getGenderFromMenu()
{
	return static_cast<MenuScreen&>(*m_screens[MENU]).getSelectedPlayer();
}


