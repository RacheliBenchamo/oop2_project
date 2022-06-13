#pragma once
#include "Screen.h"

class MenuScreen:public Screen
{
public:
	MenuScreen();
	~MenuScreen() {};

	gender getSelectedPlayer()const { return m_selectedPlayer; };

private:
	void draw(sf::RenderWindow& window)override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;

	void handleMove(const sf::Vector2f&)override;
	void setHeader();
	void setStart();
	void setHelp();
	void setExit();
	void setPick();
	void setPlayer();
	void playBackgroundSound();

	sf::Text m_header;
	sf::Text m_start;
	sf::Text m_exit;
	sf::Text m_help;
	sf::Text m_pick;
	sf::RectangleShape m_boyplayer;
	sf::RectangleShape m_girlplayer;
	gender m_selectedPlayer= WAIT;
};