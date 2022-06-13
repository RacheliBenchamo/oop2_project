

#include "ScreensInclude\Screen.h"

Screen::Screen()
{
	this->m_font = (*(FileManager::instance().getFont()));
	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
}
//----------------------------------------------------------------
screensOption Screen::activateScreen(sf::RenderWindow& window)
{
	playBackgroundSound();
	while (window.isOpen())
	{
		draw(window);
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			sf::Vector2f Location;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			case sf::Event::MouseButtonReleased:
				Location = window.mapPixelToCoords
				({ event.mouseButton.x, event.mouseButton.y });
				screensOption s = handleClick(Location, window);
				if (s != NONE)
					return s;
				break;
		
			}
		}
	}
	return CLOSE;
}
//----------------------------------------------------------------
void Screen::playMoveSound()
{
	FileManager::instance().startSound(FileManager::instance().
		getShareSaund(S_ABOVE), BUTTON_VOLUME);
}
//----------------------------------------------------------------
void Screen::playSelectSound()
{
	FileManager::instance().startSound(FileManager::instance().
		getShareSaund(S_CLICKED), BUTTON_VOLUME);
}
//----------------------------------------------------------------

void Screen::setBasicButton(sf::Text* button)
{
	button->setFont(m_font);
	button->setColor(BASE_COLOR);
	button->setCharacterSize(REG_CHAR_SIZE);
	button->setOutlineColor(OUTLINE_BASE_COLOR);
	button->setOutlineThickness(OUTLINE_THICKNESS);
}
//----------------------------------------------------------------

void Screen::setBasicHeader(sf::Text* header)
{
	header->setFont(m_font);
	header->setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	header->setCharacterSize(HEADER_SIZE);
	header->setColor(HEADER_COLOR);
	header->setOutlineColor(OUTLINE_BASE_COLOR);
	header->setOutlineThickness(OUTLINE_THICKNESS);
}