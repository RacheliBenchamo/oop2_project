#include "ScreensInclude\WinLevelScreen.h"

WinLevelScreen::WinLevelScreen()
{
	this->m_background.setTexture
	(FileManager::instance().getBackGround(WIN_GAME_BACKGROUND));

	setHeader();
	setNextLev();
	setExit();
	setMenu();
}
//------------------------------------------
//draw

void WinLevelScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header); 
	window.draw(this->m_exit);
	window.draw(this->m_menu);
	window.draw(this->m_nextLev);
	window.display();
}
//------------------------------------------
//handle click on the screen buttons

screensOption WinLevelScreen::handleClick(const sf::Vector2f& Location,
	sf::RenderWindow& window)
{
	// pressed next level
	if (this->m_nextLev.getGlobalBounds().contains(Location))
	{
		playSelectSound();
		return START;
	}
	// pressed menu
	if (this->m_menu.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		return MENU;
	}
	// pressed exit
	if (this->m_exit.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		window.close();
	}

	return NONE;
}
//------------------------------------------
//handle moving on the screen buttons

void WinLevelScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark next level button
	if (this->m_nextLev.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_nextLev.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_nextLev.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_nextLev.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_nextLev.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark menu button
	if (this->m_menu.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_menu.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_menu.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_menu.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_menu.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_exit.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}
}
//------------------------------------------
//Sets the header

void WinLevelScreen::setHeader()
{
	setBasicHeader(&m_header);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 450, 30 });
	m_header.setString("YOU FINISH THE LEVEL!");
}
//------------------------------------------
//Sets the next level button

void WinLevelScreen::setNextLev()
{
	setBasicButton(&m_nextLev);
	m_nextLev.setPosition({ SCREEN_CENTER.x - 150 , SCREEN_CENTER.y - 60 });
	m_nextLev.setString("Next Level");
}
//------------------------------------------
//Sets the menu button

void WinLevelScreen::setMenu()
{
	setBasicButton(&m_menu);
	m_menu.setPosition({ SCREEN_CENTER.x - 110 , SCREEN_CENTER.y + 60 });
	m_menu.setString("Menu");
}
//------------------------------------------
//Sets the exit button

void WinLevelScreen::setExit()
{
	setBasicButton(&m_exit);
	m_exit.setPosition({ SCREEN_CENTER.x - 90 , SCREEN_CENTER.y + 180 });
	m_exit.setString("Exit");
}
//------------------------------------------
//Play the Background Sound

void WinLevelScreen::playBackgroundSound()
{
	FileManager::instance().startSound(FileManager::instance().
		getShareSaund(S_WIN_LEVEL), VOLUME_COLLISION);
	std::this_thread::sleep_for(std::chrono::milliseconds(600));
}
