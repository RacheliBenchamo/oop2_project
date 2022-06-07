#pragma once
#include <SFML/Graphics.hpp>
#include "FileManager.h"

class Menu
{
public:
	Menu();
	~Menu() {};

	void activateMenuScreen(sf::RenderWindow&);
	gender getSelectedPlayer()const { return m_selectedPlayer; };

private:
	void helpWindow(sf::RenderWindow&);
	void draw(sf::RenderWindow& window);
	void drawHelp(sf::RenderWindow& window);
	void setHelpWindow(sf::RenderWindow&);
	bool handleClick(const sf::Vector2f&, sf::RenderWindow&);
	void handleMove(const sf::Vector2f&);
	void setHeader();
	void setStart();
	void setHelp();
	void setExit();
	void setPlayer();

	sf::Font m_font;
	sf::Text m_header;
	sf::Text m_start;
	sf::Text m_exit;
	sf::Text m_help;
	sf::RectangleShape m_background;
	sf::RectangleShape m_boyplayer;
	sf::RectangleShape m_girlplayer;
	sf::RectangleShape m_helpBackground;
	gender m_selectedPlayer=MALE;
	bool m_pressStart;
	bool m_pressHelp;

};