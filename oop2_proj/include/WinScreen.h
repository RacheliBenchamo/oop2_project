#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class WinScreen :public Screen
{
public:
	WinScreen();
	~WinScreen() {};


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
	bool m_pressMenu;
	bool m_pressExit;

};
