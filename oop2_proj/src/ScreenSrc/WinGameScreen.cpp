#include "ScreensInclude\WinGameScreen.h"

WinGameScreen::WinGameScreen()
{
	this->m_background.setTexture(FileManager::instance()
		.getBackGround(WIN_GAME_BACKGROUND));

	setHeader();
	setExit();
	setMenu();
}
//------------------------------------------
//draw

void WinGameScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_exit);
	window.draw(this->m_menu);
	window.display();
}
//------------------------------------------
//handle click on the screen buttons

screensOption WinGameScreen::handleClick(const sf::Vector2f& Location,
	sf::RenderWindow& window)
{
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

void WinGameScreen::handleMove(const sf::Vector2f& Location)
{
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

void WinGameScreen::setHeader()
{
	setBasicHeader(&m_header);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 270, 30 });
	m_header.setString("YOU WON!!!");
}
//------------------------------------------
//Sets the menu button

void WinGameScreen::setMenu()
{
	setBasicButton(&m_menu);
	m_menu.setPosition({ SCREEN_CENTER.x - 120 , SCREEN_CENTER.y - 70 });
	m_menu.setString("Menu");
}
//------------------------------------------
//Sets the exit button

void WinGameScreen::setExit()
{
	setBasicButton(&m_exit);
	m_exit.setPosition({ SCREEN_CENTER.x - 90 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
}
//------------------------------------------
//Play the Background Sound

void WinGameScreen::playBackgroundSound()
{
	FileManager::instance().startSound(FileManager::instance().
		getShareSaund(S_WIN_GAME), VOLUME_COLLISION*2);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
