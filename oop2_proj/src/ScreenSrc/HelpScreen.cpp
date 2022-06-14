#include "ScreensInclude\HelpScreen.h"

HelpScreen::HelpScreen()
{
	setMenu();
	this->m_background.setTexture
	(FileManager::instance().getBackGround(HELP_BACKGROUND));
}
//------------------------------------------
//Draw the help screen

void HelpScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_menu);
	window.display();
}
//------------------------------------------
//handle click on the screen buttons

screensOption HelpScreen::handleClick(const sf::Vector2f& Location,
	sf::RenderWindow& window)
{
	// pressed menu
	if (this->m_menu.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		return MENU;
	}
	return NONE;
}
//------------------------------------------
//handle moving on the screen buttons

void HelpScreen::handleMove(const sf::Vector2f& Location)
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
}
//------------------------------------------
//Sets the menu button

void HelpScreen::setMenu()
{
	setBasicButton(&m_menu);
	m_menu.setPosition({ SCREEN_CENTER.x - 600 
		, SCREEN_CENTER.y + 350 });
	m_menu.setString("Menu");
}