#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class Menu:public Screen
{
public:
	Menu();
	~Menu() {};

	gender getSelectedPlayer()const { return m_selectedPlayer; };

private:
	void draw(sf::RenderWindow& window)override;
	screensOption handleClick(const sf::Vector2f&, sf::RenderWindow&)override;

	void handleMove(const sf::Vector2f&)override;
	void setHeader();
	void setStart();
	void setHelp();
	void setExit();
	void setPlayer();

	sf::Text m_header;
	sf::Text m_start;
	sf::Text m_exit;
	sf::Text m_help;
	sf::RectangleShape m_boyplayer;
	sf::RectangleShape m_girlplayer;
	gender m_selectedPlayer=MALE;
	bool m_pressStart;
	bool m_pressHelp;

};