#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class HelpScreen :public Screen
{
public:
	HelpScreen();
	~HelpScreen() {};

private:
	void draw(sf::RenderWindow& window)override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;
	void handleMove(const sf::Vector2f&)override;
	void setMenu();

	sf::Font m_font;
	sf::Text m_menu;
	sf::RectangleShape m_background;
	bool m_pressMenu;
};
