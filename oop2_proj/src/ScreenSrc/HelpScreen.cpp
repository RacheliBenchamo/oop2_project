#include "ScreensInclude\HelpScreen.h"

HelpScreen::HelpScreen()
{
	this->m_font = (*(FileManager::instance().getFont()));
	setMenu();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(HELP_BACKGROUND));
}
//--------------------------------------------------

void HelpScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_menu);
	window.display();
}
//--------------------------------------------------
//handle click on the menu buttons

screensOption HelpScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{
	if (this->m_menu.getGlobalBounds().contains(Location)) // pressed start
	{
		playSelectSound();
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
//--------------------------------------------------

void HelpScreen::setMenu()
{
	setBasicButton(&m_menu);
	m_menu.setPosition({ SCREEN_CENTER.x - 600 , SCREEN_CENTER.y + 350 });
	m_menu.setString("Menu");
}