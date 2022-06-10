#include "Controller.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

Controller::Controller()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"The Diamonds Fighter!", sf::Style::Titlebar | sf::Style::Close)
	, m_playButton(true), m_levelNum(1)
{
	m_window.setFramerateLimit(60);
	setScreens();
	//menu sound
	//m_backGroundMusic.setBuffer(*FileManager::instance().getBackgraundSaund(levels(m_levelNum-1)));

	//m_currLevelBackground.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT});
}


void Controller::run() try
{
	setNewGame();

	while (m_window.isOpen())
	{
		m_window.clear();
		m_window.draw(m_currLevelBackground);
		m_dataBase.draw(m_window);
		m_statusBar.draw(m_window,m_dataBase.getPlayerPower(),
			m_dataBase.getPlayerLife(), m_dataBase.getPlayerDiamonds());
		setView();
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
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::P)
					startNewLevel();
				break;
			}
			handelEvents();
	}
}

 catch (const std::exception& e) 
 {
	std::cout << e.what();
}
//----------------------------------------------
//set the menu, background and more for starting the game

void Controller::setNewGame()
{
	m_playButton = true;
	startSound();
	setBigView();
	currScreen = MENU;
	handleScreens();
	m_playerGender = static_cast<MenuScreen&>(*m_screens[MENU]).getSelectedPlayer();
	m_board.readLevelData(m_dataBase, m_playerGender);
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel(true);
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	setBackground();

}
//----------------------------------------------
//handle the event that occurred in the curent
//round of the running

void Controller::handelEvents()
{
	m_dataBase.move(m_gameClock.restart());
	if (m_dataBase.winLevel())
		startNewLevel();
}
//----------------------------------------------
//handle the event that occurred when the MouseButtonReleased

void Controller::handelMouseButtonReleased(sf::Event event)
{
	if (m_statusBar.containsMusicIcon(event))
		handelMusicButtonReleased();
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
		//winLevelScreen();
		m_board.readLevel(m_dataBase);
		m_statusBar.updateLevel( true);
		m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	}
}
//----------------------------------------------
//starting the current level again 

void Controller::resetLevel()
{
	m_dataBase.eraseObj();
	m_board.TakeBackInputStreamToBegLevel();
	m_board.readLevelData(m_dataBase, m_playerGender);
	//read all the char from the text:
	m_board.readLevel(m_dataBase);
	this->m_statusBar.updateLevel( false);
}
//------------------------------------------
//starting new game

void Controller::startSound()
{
	m_backGroundMusic.setBuffer
	(*FileManager::instance().getBackgraundSaund(levels(m_levelNum - 1)));
	m_backGroundMusic.play();
	m_backGroundMusic.setLoop(true);
	m_backGroundMusic.setVolume(VOLUME_BG);
}
//------------------------------------

void Controller::startnewGame()
{
	m_gameClock.restart();
	m_board.resetInputStream();
	m_statusBar.resetNumOfLevel();
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	m_dataBase.setLevel();
	currScreen = WIN;
	setBigView();
	handleScreens();
	m_levelNum=1;
	setBackground();
	run();
}
//-----------------------------------------------------------

void Controller::setScreens()
{
	m_screens.push_back(std::make_unique<HelpScreen>());
	m_screens.push_back(std::make_unique<MenuScreen>());
	m_screens.push_back(std::make_unique<LoseScreen>());
	m_screens.push_back(std::make_unique<WinScreen>());
}
//-----------------------------------------------------------
void Controller::handleScreens()
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
		case RESTART:
			currScreen = NONE;
			resetLevel();
			break;
		case START:
			currScreen = NONE;
			break;
		default:
			break;
		}
	}
}
//-----------------------------------------------------------

void Controller::setBigView()
{
	m_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	m_window.setView(m_view);
}

//---------------------------------------------------------

void Controller::setBackground()
{
	m_currLevelBackground = sf::RectangleShape(sf::Vector2f({ CAMERA_WIDTH,CAMERA_HEIGHT }));
	m_currLevelBackground.setOrigin(m_currLevelBackground.getSize() / 2.f);
	switch (m_levelNum)
	{
	case STAGE_ONE:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL1_BACKGROUND));
		break;
	case STAGE_TWO:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL2_BACKGROUND));
		break;
	case STAGE_THREE:
		m_currLevelBackground.setTexture(FileManager::instance().getBackGround(LEVEL3_BACKGROUND));
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------

void Controller::setView()
{
	setViewToCenter();
	m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	m_window.setView(m_view);
	m_currLevelBackground.setPosition(m_view.getCenter());
	m_statusBar.updatePos(m_view.getCenter());
	//m_currLevelBackground.setPosition(m_currLevelBackground.getPosition().x +400, 
	//m_currLevelBackground.getPosition().y +200);
}
//-----------------------------------------------------------
// 
//set view center by player pos and level size.
void Controller::setViewToCenter()
{
	sf::Vector2f pos, playerPos=m_dataBase.getPlayerPos();
	pos = playerPos;

	if((playerPos.x< m_dataBase.getLevelSize().y * Y_SPACE
		+ START_SPACE * 3.5 - CAMERA_WIDTH / 2)&& 
		(playerPos.x > START_SPACE * 3.5+CAMERA_WIDTH / 2)
		&& (playerPos.y < m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE/2  - CAMERA_HEIGHT / 2))
		m_view.setCenter(playerPos.x, playerPos.y);

	else
	{
		if ((playerPos.x > m_dataBase.getLevelSize().y * Y_SPACE
			+ START_SPACE * 3.5 - CAMERA_WIDTH / 2))
			pos.x = playerPos.x-(playerPos.x - (m_dataBase.getLevelSize().y * Y_SPACE
				+ START_SPACE * 3.5 - CAMERA_WIDTH / 2));

		else if(playerPos.x < START_SPACE*1.6 +CAMERA_WIDTH / 2)
			pos.x= playerPos.x +( START_SPACE * 1.6 +CAMERA_WIDTH / 2- playerPos.x );

		if(playerPos.y > m_dataBase.getLevelSize().x * X_SPACE
			+ START_SPACE/2  - CAMERA_HEIGHT / 2)
			pos.y = playerPos.y - (playerPos.y - (m_dataBase.getLevelSize().x * X_SPACE
				+START_SPACE/2 - CAMERA_HEIGHT / 2));

		m_view.setCenter(pos);
	}
}
