#include "ScreensInclude\GameScreen.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

GameScreen::GameScreen(sf::RenderWindow& window,Controller* controller)
	:m_playButton(true), m_levelNum(1), m_controller(controller), m_window(&window)
{
}
//------------------------------------------
//Activate the game screen

screensOption GameScreen::activateScreen(sf::RenderWindow& window) try
{
	setNewGame();
	playBackgroundSound();

	while (window.isOpen())
	{
		window.clear();
		window.draw(m_currLevelBackground);
		m_dataBase.draw(window, m_playButton);
		m_statusBar.draw(window, m_dataBase.getPlayerPower(),
			m_dataBase.getPlayerLife(), m_dataBase.getPlayerDiamonds());
		setView();
		window.display();

		for (auto event = sf::Event(); window.pollEvent(event); )
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				handelMouseButtonReleased(window.mapPixelToCoords
				({ event.mouseButton.x, event.mouseButton.y }));
				break;
			}
		if (m_playButton)
			handelEvents();
	}
	return CLOSE;
}

catch (const std::exception& e)
{
	std::cout << e.what();
}
//------------------------------------------
//Sets the menu, background and more for
//starting the game

void GameScreen::setNewGame()
{
	m_playButton = true;
	setBigView();
	m_controller->handleScreens(MENU);
	m_playerGender = m_controller->getGenderFromMenu();
	m_dataBase.setLevelMaxDiamonds(0);
	m_board.readLevelData(m_dataBase, m_playerGender);
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel(true);
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	setBackground();
}
//------------------------------------------
//Handle the event that occurred in the curent
//round of the running

void GameScreen::handelEvents()
{
	m_dataBase.move(m_gameClock.restart());

	if (m_dataBase.winLevel())
		startNewLevel();
	if (m_dataBase.loseLevel())
	{
		setBigView();
		m_controller->handleScreens(LOSE);
		m_playerGender = m_controller->getGenderFromMenu();
		resetLevel();
		playBackgroundSound();
	}
}
//------------------------------------------
//Handle the event that occurred when the
//MouseButtonReleased

void GameScreen::handelMouseButtonReleased(const sf::Vector2f pos )
{
	if (m_statusBar.containsMusicIcon(pos))
		handelMusicButtonReleased();

	if (m_statusBar.containsSoundIcon(pos))
		handelSoundButtonReleased();

	if (m_statusBar.containsRestartIcon(pos))
		this->resetLevel();

	if (m_statusBar.containsStopAndPlayIcon(pos))
		handelStopPlayButtonReleased();
}
//------------------------------------------
//Stopping or playing background music

void GameScreen::handelMusicButtonReleased()
{
	FileManager::instance().setBackgroundMusic();
	playBackgroundSound();
	m_statusBar.changeMusicIcon();
}
//------------------------------------------
//pouse or keep going the level

void GameScreen::handelStopPlayButtonReleased()
{
	m_playButton ? m_playButton = false : m_playButton = true;
	m_statusBar.changePlayIcon();
}
//------------------------------------------
//Stopping or playing background sounds

void GameScreen::handelSoundButtonReleased()
{
	FileManager::instance().setAudiodMusic();
	m_statusBar.changeSoundIcon();
}
//------------------------------------------
//Starting new level

void GameScreen::startNewLevel()
{
	m_dataBase.eraseObj();

	//if there is no more levels
	if (!m_board.readLevelData(m_dataBase, m_playerGender))
	{
		startnewGame();
	}
	else
	{
		m_levelNum++;
		playBackgroundSound();
		setBigView();
		if (m_levelNum != 1) { m_controller->handleScreens(WIN_LEVEL); }
		m_playerGender = m_controller->getGenderFromMenu();
		m_dataBase.setGender(m_playerGender);
		m_dataBase.setLevelMaxDiamonds(0);
		m_dataBase.setCurrLevel(m_levelNum);
		setBackground();
		m_board.readLevel(m_dataBase);
		m_statusBar.updateLevel(true);
		m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	}
}
//------------------------------------------
//Starting the current level again 

void GameScreen::resetLevel()
{
	m_dataBase.eraseObj();
	m_board.TakeBackInputStreamToBegLevel();
	m_board.readLevelData(m_dataBase, m_playerGender);
	//read all the char from the text:
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel(false);
}
//------------------------------------------
//Starting new game

void GameScreen::startnewGame()
{
	m_gameClock.restart();
	m_board.resetInputStream();
	m_statusBar.resetNumOfLevel();
	m_dataBase.resetLevel();
	setBigView();
	m_levelNum = 0;
	m_controller-> handleScreens(WIN_GAME);
}
//------------------------------------------
//Sets the window to be in full view 

void GameScreen::setBigView()
{
	m_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_window->setView(m_view);
}
//------------------------------------------
//Plays the background sound of the game

void GameScreen::playBackgroundSound()
{
	FileManager::instance().startBackgraundSound(FileManager::instance().
		getBackgraundSaund(m_dataBase.getStageType()), VOLUME_BG);
}
//------------------------------------------
//Sets the background picture of the game

void GameScreen::setBackground()
{
	m_currLevelBackground = sf::RectangleShape
	(sf::Vector2f({ CAMERA_WIDTH,CAMERA_HEIGHT }));
	m_currLevelBackground.setOrigin
	(m_currLevelBackground.getSize() / 2.f);
	switch (m_dataBase.getStageType())
	{
	case FOREST:
		m_currLevelBackground.setTexture
		(FileManager::instance().getBackGround(FOREST_BACKGROUND));
		break;
	case SNOW:
		m_currLevelBackground.setTexture
		(FileManager::instance().getBackGround(SNOW_BACKGROUND));
		break;
	case DESERT:
		m_currLevelBackground.setTexture
		(FileManager::instance().getBackGround(DESERT_BACKGROUND));
		break;
	default:
		break;
	}
}
//------------------------------------------
//Sets the view to be on the player all the time

void GameScreen::setView()
{
	setViewToCenter();
	m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	m_window->setView(m_view);
	m_currLevelBackground.setPosition(m_view.getCenter());
	m_statusBar.updatePos(m_view.getCenter());
}
//------------------------------------------
//Sets view center by player pos and level size.

void GameScreen::setViewToCenter()
{
	sf::Vector2f pos, playerPos = m_dataBase.getPlayerPos();
	pos = playerPos;

	if ((playerPos.x < m_dataBase.getLevelSize().y * Y_SPACE
		+ START_SPACE * 3.5 - CAMERA_WIDTH / 2) &&
		(playerPos.x >= START_SPACE * 2 + CAMERA_WIDTH / 2)
		&& (playerPos.y < m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE / 2 - CAMERA_HEIGHT / 2))
		m_view.setCenter(playerPos.x, playerPos.y);

	else
	{
		if ((playerPos.x >= m_dataBase.getLevelSize().y * Y_SPACE
			+ START_SPACE * 2 - CAMERA_WIDTH / 2))
			pos.x = playerPos.x - (playerPos.x -
				(m_dataBase.getLevelSize().y * Y_SPACE
				+ START_SPACE * 2 - CAMERA_WIDTH / 2));

		else if (playerPos.x < START_SPACE * 1.6 + CAMERA_WIDTH / 2)
			pos.x = playerPos.x + (START_SPACE * 1.6 + CAMERA_WIDTH / 2 
				- playerPos.x);

		if (playerPos.y > m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE / 2 - CAMERA_HEIGHT / 2)
			pos.y = playerPos.y - (playerPos.y - 
				(m_dataBase.getLevelSize().x * X_SPACE
				+ START_SPACE / 2 - CAMERA_HEIGHT / 2));

		m_view.setCenter(pos);
	}
}
