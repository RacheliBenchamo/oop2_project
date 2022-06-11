#include "ScreensInclude\GameScreen.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

GameScreen::GameScreen(sf::RenderWindow& window,Controller* controller)
	:m_playButton(true), m_levelNum(1), m_controller(controller), m_window(&window)
{
	//menu sound
	//m_backGroundMusic.setBuffer(*FileManager::instance()
	//.getBackgraundSaund(levels(m_levelNum-1)));

	//m_currLevelBackground.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT});
}


screensOption GameScreen::activateScreen(sf::RenderWindow& window) try
{
	
	setNewGame();

	while (window.isOpen())
	{
		window.clear();
		window.draw(m_currLevelBackground);
		m_dataBase.draw(window);
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
				handelMouseButtonReleased(event);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::R)
					resetLevel();
				//to delete
				if (event.key.code == sf::Keyboard::P)
					startNewLevel();
				break;
			}
		handelEvents();
	}
	return CLOSE;
}

catch (const std::exception& e)
{
	std::cout << e.what();
}
//----------------------------------------------
//set the menu, background and more for starting the game

void GameScreen::setNewGame()
{
	m_playButton = true;
	startSound();
	setBigView();
	m_controller->handleScreens(MENU);
	m_playerGender = m_controller->getGenderFromMenu();
	m_board.readLevelData(m_dataBase, m_playerGender);
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel(true);
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	setBackground();

}
//----------------------------------------------
//handle the event that occurred in the curent
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
		resetLevel();
	}


}
//----------------------------------------------
//handle the event that occurred when the MouseButtonReleased

void GameScreen::handelMouseButtonReleased(sf::Event event)
{
	if (m_statusBar.containsMusicIcon(event))
		handelMusicButtonReleased();
}
//----------------------------------------------
//stopping or playing background music

void GameScreen::handelMusicButtonReleased()
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

void GameScreen::handelStopPlayButtonReleased()
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

void GameScreen::startNewLevel()
{
	m_dataBase.eraseObj();

	//if there is no more levels
	if (!m_board.readLevelData(m_dataBase, m_playerGender))
		startnewGame();
	else
	{
		m_levelNum++;
		startSound();
		m_dataBase.setCurrLevel(m_levelNum);
		setBackground();
		m_board.readLevel(m_dataBase);
		m_statusBar.updateLevel(true);
		m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	}
}
//----------------------------------------------
//starting the current level again 

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
//starting new game

void GameScreen::startSound()
{
	m_backGroundMusic.setBuffer
	(*FileManager::instance().getBackgraundSaund(levels(m_levelNum - 1)));
	m_backGroundMusic.play();
	m_backGroundMusic.setLoop(true);
	m_backGroundMusic.setVolume(VOLUME_BG);
}
//------------------------------------

void GameScreen::startnewGame()
{
	m_gameClock.restart();
	m_board.resetInputStream();
	m_statusBar.resetNumOfLevel();
	m_dataBase.resetLevel();
	setBigView();
	m_levelNum = 1;
	m_controller-> handleScreens(WIN);
}

//-----------------------------------------------------------

void GameScreen::setBigView()
{
	m_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_window->setView(m_view);
}

//---------------------------------------------------------

void GameScreen::setBackground()
{
	m_currLevelBackground = sf::RectangleShape(sf::Vector2f({ CAMERA_WIDTH,CAMERA_HEIGHT }));
	m_currLevelBackground.setOrigin(m_currLevelBackground.getSize() / 2.f);
	switch (m_levelNum - 1)
	{
	case LEVEL1:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL1_BACKGROUND));
		break;
	case LEVEL2:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL2_BACKGROUND));
		break;
	case LEVEL3:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL3_BACKGROUND));
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------

void GameScreen::setView()
{
	setViewToCenter();
	m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	m_window->setView(m_view);
	m_currLevelBackground.setPosition(m_view.getCenter());
	m_statusBar.updatePos(m_view.getCenter());
}
//-----------------------------------------------------------
// 
//set view center by player pos and level size.
void GameScreen::setViewToCenter()
{
	sf::Vector2f pos, playerPos = m_dataBase.getPlayerPos();
	pos = playerPos;

	if ((playerPos.x < m_dataBase.getLevelSize().y * Y_SPACE
		+ START_SPACE * 3.5 - CAMERA_WIDTH / 2) &&
		(playerPos.x > START_SPACE * 3.3 + CAMERA_WIDTH / 2)
		&& (playerPos.y < m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE / 2 - CAMERA_HEIGHT / 2))
		m_view.setCenter(playerPos.x, playerPos.y);

	else
	{
		if ((playerPos.x >= m_dataBase.getLevelSize().y * Y_SPACE
			+ START_SPACE * 3.3 - CAMERA_WIDTH / 2))
			pos.x = playerPos.x - (playerPos.x - (m_dataBase.getLevelSize().y * Y_SPACE
				+ START_SPACE * 3.3 - CAMERA_WIDTH / 2));

		else if (playerPos.x < START_SPACE * 1.6 + CAMERA_WIDTH / 2)
			pos.x = playerPos.x + (START_SPACE * 1.6 + CAMERA_WIDTH / 2 - playerPos.x);

		if (playerPos.y > m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE / 2 - CAMERA_HEIGHT / 2)
			pos.y = playerPos.y - (playerPos.y - (m_dataBase.getLevelSize().x * X_SPACE
				+ START_SPACE / 2 - CAMERA_HEIGHT / 2));

		m_view.setCenter(pos);
	}
}
