

#include "ScreensInclude\Screen.h"

Screen::Screen()
{
	this->m_font = (*(FileManager::instance().getFont()));
	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
}
//----------------------------------------------------------------
screensOption Screen::activateScreen(sf::RenderWindow& window)
{
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
	FileManager::instance().startSound(FileManager::instance().getShareSaund(S_ABOVE), BUTTON_VOLUME);
}
//----------------------------------------------------------------
void Screen::playSelectSound()
{
	FileManager::instance().startSound(FileManager::instance().getShareSaund(S_CLICKED), BUTTON_VOLUME);
}
