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
	virtual void draw(sf::RenderWindow& window) =0;
	virtual screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&) =0;
	virtual void handleMove(const sf::Vector2f&)=0;

protected:
	sf::RectangleShape m_background;
	sf::Font m_font;
};