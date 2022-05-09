#include "Controller.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

Controller::Controller()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT),
		"Save the king!", sf::Style::Titlebar | sf::Style::Close)
	, m_playButton(true)
{
	m_window.setFramerateLimit(60);

	m_backGroundMusic.setBuffer(*FileManager::p2FileManager().getSound(S_BACKROUND));

	m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	m_background.setTexture(FileManager::p2FileManager().getBackGround(GAME_BACKGROUND));
}
//--------------------------------------------------
//start the game

void Controller::run()
{
	setNewGame();

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_background);
		m_dataBase.draw(m_window);
		m_statusBar.draw(m_window);
		m_window.display();

		for (auto event = sf::Event(); m_window.pollEvent(event); )
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				handelMouseButtonReleased(event);
				break;
			}

		if (m_playButton)
			handelEvents();
		else
			m_statusBar.resetTimer();
	}
}
//----------------------------------------------
//set the menu, background and more for starting the game

void Controller::setNewGame()
{
	m_backGroundMusic.play();
	m_backGroundMusic.setLoop(true);
	m_backGroundMusic.setVolume(VOLUME_BG);

	m_playButton = true;

	m_menu.activateMenuScreen(m_window);

	m_board.readLevelData(m_dataBase);
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel(true);
}
//----------------------------------------------
//handle the event that occurred in the curent
//round of the running

void Controller::handelEvents()
{
	m_dataBase.move(m_gameClock.restart());
	if (m_dataBase.winLevel())
		startNewLevel();
	/*if (m_statusBar.getTime() <= 0)
		resetLevel();*/
}
//----------------------------------------------
//handle the event that occurred when the MouseButtonReleased

void Controller::handelMouseButtonReleased(sf::Event event)
{
	if (m_statusBar.containsMusicIcon(event))
		handelMusicButtonReleased();

	if (m_statusBar.containsStopAndPlayIcon(event))
		handelStopPlayButtonReleased();

	if (m_statusBar.containsRestartIcon(event))
		resetLevel();
}
//----------------------------------------------
//stopping or playing background music

void Controller::handelMusicButtonReleased()
{

	if (m_backGroundMusic.getStatus() == sf::SoundSource::Status::Playing)
	{
		m_backGroundMusic.stop();
		m_statusBar.setMusicIcon(false);
	}
	else
	{
		m_backGroundMusic.play();
		m_statusBar.setMusicIcon(true);
	}
}
//----------------------------------------------
//pouse or keep going the level

void Controller::handelStopPlayButtonReleased()
{
	if (m_playButton)
	{
		m_playButton = false;
		m_statusBar.setStopAndPlayIcon(false);
	}
	else
	{
		m_playButton = true;
		m_statusBar.setStopAndPlayIcon(true);
	}
}
//----------------------------------------------
//starting new level

void Controller::startNewLevel()
{
	sf::Sound winSound;

	m_dataBase.eraseObj();

	if (!m_board.readLevelData(m_dataBase)) //if there is no more levels
		startnewGame();
	else
	{
		winLevelScreen();
		m_board.readLevel(m_dataBase);
		this->m_statusBar.updateLevel( true);
	}
}
//------------------------------------------
//starting new game

void Controller::startnewGame()
{
	m_gameClock.restart();
	m_board.resetInputStream();
	m_statusBar.resetNumOfLevel();
	winGameScreen();
	run();
}
//----------------------------------------------
//starting the current level again 

void Controller::resetLevel()
{
	m_dataBase.eraseObj();
	m_board.TakeBackInputStreamToBegLevel();
	m_board.readLevelData(m_dataBase);//board size and time
	//read all the char from the text:
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel( false);
}

//---------------------------------------------
//set the win game screen

void Controller::winGameScreen()
{
	setWinScreen(WIN_GAME_BACKGROUND, S_WIN_GAME);
}
//---------------------------------------------
//set the win level screen

void Controller::winLevelScreen()
{
	setWinScreen(WIN_LEVEL_BACKGROUND, S_WIN_LEVEL);
}
//---------------------------------------------------------
//set the relevant wining screen

void Controller::setWinScreen(backgroundsType backgroundType, sounds soundType)
{
	sf::Sound effect;
	effect.setBuffer(*FileManager::p2FileManager().getSound(soundType));
	effect.setVolume(VOLUME_BG);
	effect.play();

	sf::RectangleShape background;
	background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	background.setTexture(FileManager::p2FileManager().getBackGround(backgroundType));

	for (int i = 0; i < WIN_WIAT && m_window.isOpen(); i++)
	{
		m_window.clear(sf::Color::White);
		m_window.draw(background);
		m_window.display();
	}
}
