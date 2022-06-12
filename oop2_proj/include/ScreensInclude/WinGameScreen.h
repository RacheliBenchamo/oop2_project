#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class WinGameScreen :public Screen
{
public:
	WinGameScreen();
	~WinGameScreen() {};


private:
	void draw(sf::RenderWindow& window) override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;
	void handleMove(const sf::Vector2f&)override;
	void setHeader();
	void setMenu();
	void setExit();

	sf::Text m_header;
	sf::Text m_menu;
	sf::Text m_exit;
};
