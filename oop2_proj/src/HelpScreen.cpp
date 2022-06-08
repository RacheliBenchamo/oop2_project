#include "..\include\HelpScreen.h"

HelpScreen::HelpScreen()
{
	this->m_font = (*(FileManager::instance().getFont()));
	setMenu();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(HELP_BACKGROUND));
}


//--------------------------------------------------
//handle click on the menu buttons

void HelpScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_menu);
	window.display();
}

screensOption HelpScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{
	if (this->m_menu.getGlobalBounds().contains(Location)) // pressed start
	{
		return MENU;
	}
	return NONE;
}
//--------------------------------------------------
//handle moving on the menu buttons

void HelpScreen::handleMove(const sf::Vector2f& Location)
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

}

void HelpScreen::setMenu()
{
	m_menu.setFont(m_font);
	m_menu.setColor(sf::Color(153, 153, 255, 255));
	m_menu.setCharacterSize(REG_CHAR_SIZE);
	m_menu.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y - 70 });
	m_menu.setString("Menu");
	m_menu.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_menu.setOutlineThickness(OUTLINE_THICKNESS);
}