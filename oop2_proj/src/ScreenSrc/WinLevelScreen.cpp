#include "ScreensInclude\WinLevelScreen.h"

WinLevelScreen::WinLevelScreen()
{
	this->m_font = (*(FileManager::instance().getFont()));

	setHeader();
	setNextLev();
	setExit();
	setMenu();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(WIN_GAME_BACKGROUND));
}
//--------------------------------------------------
//handle click on the menu buttons

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
//--------------------------------------------------

screensOption WinLevelScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{

	if (this->m_nextLev.getGlobalBounds().contains(Location)) // pressed start
	{
		playSelectSound();
		return START;
	}
	if (this->m_menu.getGlobalBounds().contains(Location)) // pressed start
	{
		playSelectSound();
		return MENU;
	}
	if (this->m_exit.getGlobalBounds().contains(Location)) // pressed exit
	{
		playSelectSound();
		window.close();
	}

	return NONE;
}
//--------------------------------------------------
//handle moving on the menu buttons

void WinLevelScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
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
	// mark/unmark start button
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

void WinLevelScreen::setHeader()
{
	m_header.setFont(m_font);
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 450, 30 });
	m_header.setString("YOU FINISH THE LEVEL!");
	m_header.setColor(HEADER_COLOR);
	m_header.setOutlineColor(OUTLINE_BASE_COLOR);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);
}

void WinLevelScreen::setNextLev()
{
	m_nextLev.setFont(m_font);
	m_nextLev.setColor(BASE_COLOR);
	m_nextLev.setCharacterSize(REG_CHAR_SIZE);
	m_nextLev.setPosition({ SCREEN_CENTER.x - 150 , SCREEN_CENTER.y - 60 });
	m_nextLev.setString("Next Level");
	m_nextLev.setOutlineColor(OUTLINE_BASE_COLOR);
	m_nextLev.setOutlineThickness(OUTLINE_THICKNESS);
}

void WinLevelScreen::setMenu()
{
	m_menu.setFont(m_font);
	m_menu.setColor(BASE_COLOR);
	m_menu.setCharacterSize(REG_CHAR_SIZE);
	m_menu.setPosition({ SCREEN_CENTER.x - 110 , SCREEN_CENTER.y + 60 });
	m_menu.setString("Menu");
	m_menu.setOutlineColor(OUTLINE_BASE_COLOR);
	m_menu.setOutlineThickness(OUTLINE_THICKNESS);
}


void WinLevelScreen::setExit()
{
	m_exit.setFont(m_font);
	m_exit.setColor(BASE_COLOR);
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ SCREEN_CENTER.x - 90 , SCREEN_CENTER.y + 180 });
	m_exit.setString("Exit");
	m_exit.setOutlineColor(OUTLINE_BASE_COLOR);
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
}
