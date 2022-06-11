#include "ScreensInclude\LoseScreen.h"

LoseScreen::LoseScreen()
{
	this->m_font = (*(FileManager::instance().getFont()));

	setHeader();
	setExit();
	setMenu();
	setRestart();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(LOSE_LEVEL_BACKGROUND));
}

//--------------------------------------------------
//handle click on the menu buttons

void LoseScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_exit);
	window.draw(this->m_menu);
	window.draw(this->m_restart);
	window.display();
}

screensOption LoseScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{
	if (this->m_menu.getGlobalBounds().contains(Location)) // pressed menu
	{
		return MENU;
	}
	if (this->m_restart.getGlobalBounds().contains(Location)) // pressed restart
	{
		return RESTART;
	}

	if (this->m_exit.getGlobalBounds().contains(Location)) // pressed exit
		window.close();
	return NONE;
}
//--------------------------------------------------
//handle moving on the menu buttons

void LoseScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
	if (this->m_menu.getGlobalBounds().contains(Location))
	{
		this->m_menu.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_menu.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_menu.setOutlineColor(sf::Color::Black);
		this->m_menu.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		this->m_exit.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(sf::Color::Black);
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark restart button
	if (this->m_restart.getGlobalBounds().contains(Location))
	{
		this->m_restart.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_restart.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_restart.setOutlineColor(sf::Color::Black);
		this->m_restart.setOutlineThickness(OUTLINE_THICKNESS);
	}
}
void LoseScreen::setHeader()
{
	m_header.setFont(m_font);
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 290, 30 });
	m_header.setString("YOU LOSE...");
	m_header.setColor(sf::Color(204, 204, 255, 255));
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);
}

void LoseScreen::setMenu()
{
	m_menu.setFont(m_font);
	m_menu.setColor(sf::Color(153, 153, 255, 255));
	m_menu.setCharacterSize(REG_CHAR_SIZE);
	m_menu.setPosition({ SCREEN_CENTER.x - 145 , SCREEN_CENTER.y - 60 });
	m_menu.setString("Menu");
	m_menu.setOutlineColor(sf::Color::Black);
	m_menu.setOutlineThickness(OUTLINE_THICKNESS);
}


void LoseScreen::setExit()
{
	m_exit.setFont(m_font);
	m_exit.setColor(sf::Color(153, 153, 255, 255));
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ SCREEN_CENTER.x - 115 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
	m_exit.setOutlineColor(sf::Color::Black);
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
}
void LoseScreen::setRestart()
{
	m_restart.setFont(m_font);
	m_restart.setColor(sf::Color(153, 153, 255, 255));
	m_restart.setCharacterSize(REG_CHAR_SIZE);
	m_restart.setPosition({ SCREEN_CENTER.x - 160 , SCREEN_CENTER.y + 180 });
	m_restart.setString("Rastart");
	m_restart.setOutlineColor(sf::Color::Black);
	m_restart.setOutlineThickness(OUTLINE_THICKNESS);
}
