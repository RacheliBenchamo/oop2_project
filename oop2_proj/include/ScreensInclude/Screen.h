#pragma once
#include "FileManager.h"

class Screen
{
public:
	Screen();
	~Screen() {};

	virtual screensOption activateScreen(sf::RenderWindow&);
	void playMoveSound();
	void playSelectSound();
	virtual void playBackgroundSound()=0;
	virtual void draw(sf::RenderWindow& window) =0;
	virtual screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&) =0;
	virtual void handleMove(const sf::Vector2f&)=0;

protected:
	void setBasicButton(sf::Text*);
	void setBasicHeader(sf::Text* m_button);
	sf::RectangleShape m_background;
	sf::Font m_font;

};