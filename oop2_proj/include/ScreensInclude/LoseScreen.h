#pragma once
#include "Screen.h"

class LoseScreen :public Screen
{
public:
	LoseScreen();
	~LoseScreen() {};

private:
	void draw(sf::RenderWindow& window)override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;
	void handleMove(const sf::Vector2f&)override;
	void setHeader();
	void setMenu();
	void setExit();
	void setRestart();
	void playBackgroundSound();

	sf::Text m_menu,
		m_header,
		m_restart,
		m_exit;
};
