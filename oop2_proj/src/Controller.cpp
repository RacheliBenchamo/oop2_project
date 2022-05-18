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
	, m_playButton(true)
{
	m_window.setFramerateLimit(60);

	m_backGroundMusic.setBuffer(*FileManager::p2FileManager().getSound(S_BACKROUND));

	//m_currLevelBackground = sf::RectangleShape(sf::Vector2f({ CAMERA_WIDTH,CAMERA_HEIGHT }));
	m_currLevelBackground.setOrigin(m_currLevelBackground.getSize() / 2.f);
	//m_currLevelBackground.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT});
	m_currLevelBackground.setTexture(FileManager::p2FileManager().getBackGround(LEVEL1_BACKGROUND));
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
		//setView();
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

 catch (const std::exception& e) {
	std::cout << e.what();
 
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
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());

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
		
		m_levelNum++;
		m_dataBase.setCurrLevel(m_levelNum);
		setBackground();
		winLevelScreen();
		m_board.readLevel(m_dataBase);
		m_statusBar.updateLevel( true);
		m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());
	}
}
//------------------------------------------
//starting new game

void Controller::startnewGame()
{
	m_gameClock.restart();
	m_board.resetInputStream();
	m_statusBar.resetNumOfLevel();
	m_statusBar.setMaxDiamonds(m_dataBase.getLevelMaxDiamonds());

	winGameScreen();
	m_levelNum=1;
	setBackground();
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
//---------------------------------------------------------

void Controller::setBackground()
{
	switch (m_levelNum)
	{
	case STAGE_ONE:
		m_currLevelBackground.setTexture(FileManager::p2FileManager().getBackGround(LEVEL1_BACKGROUND));
		break;
	case STAGE_TWO:
		m_currLevelBackground.setTexture(FileManager::p2FileManager().getBackGround(LEVEL2_BACKGROUND));
		break;
	case STAGE_THREE:
		m_currLevelBackground.setTexture(FileManager::p2FileManager().getBackGround(LEVEL3_BACKGROUND));
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------

void Controller::setView()
{
	m_view.setCenter(m_dataBase.getPlayerPos().x,m_dataBase.getPlayerPos().y);
	m_view.setSize(CAMERA_WIDTH, CAMERA_HEIGHT);
	m_window.setView(m_view);
	m_currLevelBackground.setPosition(m_view.getCenter());
	m_statusBar.updatePos(m_view.getCenter());
	//m_currLevelBackground.setPosition(m_currLevelBackground.getPosition().x +400, m_currLevelBackground.getPosition().y +200);
}