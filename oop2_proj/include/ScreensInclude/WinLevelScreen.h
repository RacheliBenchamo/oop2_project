#pragma once
#include "Screen.h"

class WinLevelScreen :public Screen
{
public:
	WinLevelScreen();
	~WinLevelScreen() {};

private:
	void draw(sf::RenderWindow& window) override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;
	void handleMove(const sf::Vector2f&)override;
	void setHeader();
	void setNextLev();
	void setMenu();
	void setExit();
	void playBackgroundSound();

	sf::Text m_header;
	sf::Text m_nextLev;
	sf::Text m_menu;
	sf::Text m_exit;
};
