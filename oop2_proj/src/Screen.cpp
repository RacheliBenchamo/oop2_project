

#include "..\include\Screen.h"

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
}
//----------------------------------------------------------------
void Screen::playMoveSound()
{
	static sf::Sound effect;
	effect.setBuffer(*FileManager::instance().getShareSaund(S_ABOVE));
	effect.play();
	effect.setVolume(BUTTON_VOLUME);
}
//----------------------------------------------------------------
void Screen::playSelectSound()
{
	static sf::Sound effect;
	effect.setBuffer(*FileManager::instance().getShareSaund(S_CLICKED));
	effect.play();
	effect.setVolume(BUTTON_VOLUME);
}
