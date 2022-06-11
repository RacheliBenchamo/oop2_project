#include "..\include\WinScreen.h"

WinScreen::WinScreen()
{
	this->m_font = (*(FileManager::instance().getFont()));

	setHeader();
	setExit();
	setMenu();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(WIN_GAME_BACKGROUND));
}
//--------------------------------------------------
//handle click on the menu buttons

void WinScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_exit);
	window.draw(this->m_menu);
	window.display();
}

screensOption WinScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{
	if (this->m_menu.getGlobalBounds().contains(Location)) // pressed start
	{
		return MENU;
	}

	if (this->m_exit.getGlobalBounds().contains(Location)) // pressed exit
		window.close();

	return NONE;
}
//--------------------------------------------------
//handle moving on the menu buttons

void WinScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
	if (this->m_menu.getGlobalBounds().contains(Location))
	{
		this->m_menu.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_menu.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_menu.setOutlineColor(sf::Color(230, 230, 255, 255));
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
		this->m_exit.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}

}

void WinScreen::setHeader()
{
	m_header.setFont(m_font);
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 330, 30 });
	m_header.setString("YOU WON!!!");
	m_header.setColor(sf::Color(204, 204, 255, 255));
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);
}

void WinScreen::setMenu()
{
	m_menu.setFont(m_font);
	m_menu.setColor(sf::Color(153, 153, 255, 255));
	m_menu.setCharacterSize(REG_CHAR_SIZE);
	m_menu.setPosition({ SCREEN_CENTER.x - 120 , SCREEN_CENTER.y - 70 });
	m_menu.setString("Menu");
	m_menu.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_menu.setOutlineThickness(OUTLINE_THICKNESS);
}


void WinScreen::setExit()
{
	m_exit.setFont(m_font);
	m_exit.setColor(sf::Color(153, 153, 255, 255));
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ SCREEN_CENTER.x - 90 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
	m_exit.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
}
