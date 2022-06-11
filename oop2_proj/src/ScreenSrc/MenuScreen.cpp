#pragma warning (disable : 4996)
#include "ScreensInclude\MenuScreen.h"
#include "Macros.h"
#include <iostream>

//--------------------------------------------------
//constructor

MenuScreen::MenuScreen()
	:m_pressStart(false), m_pressHelp(false)
{
	this->m_font=(*(FileManager::instance().getFont()));

	setHeader();
	setStart();
	setExit();
	setHelp();
	setPick();
	setPlayer();


	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::instance().getBackGround(MENU_BACKGROUND));
}
//--------------------------------------------------
//set the header details

void MenuScreen::setHeader()
{
	m_header.setFont(m_font);
	m_header.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
	m_header.setCharacterSize(HEADER_SIZE);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 370, 30 });
	m_header.setString("The Diamonds Fighter");
	m_header.setColor(sf::Color(204, 204, 255, 255));
	m_header.setOutlineColor(sf::Color::Black);
	m_header.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//set the start details

void MenuScreen::setStart()
{
	m_start.setFont(m_font);
	m_start.setColor(sf::Color(153, 153, 255, 255));
	m_start.setCharacterSize(REG_CHAR_SIZE);
	m_start.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y - 70 });
	m_start.setString("Start");
	m_start.setOutlineColor(sf::Color::Black);
	m_start.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//set the help details

void MenuScreen::setHelp()
{
	m_help.setFont(m_font);
	m_help.setColor(sf::Color(153, 153, 255, 255));
	m_help.setCharacterSize(REG_CHAR_SIZE);
	m_help.setPosition({ SCREEN_CENTER.x - 40, SCREEN_CENTER.y + 190 });
	m_help.setString("Help");
	m_help.setOutlineColor(sf::Color::Black);
	m_help.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//set the exit details

void MenuScreen::setExit()
{
	m_exit.setFont(m_font);
	m_exit.setColor(sf::Color(153, 153, 255, 255));
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
	m_exit.setOutlineColor(sf::Color::Black);
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
}
//---------------------------------

void MenuScreen::setPick()
{
	m_pick.setFont(m_font);
	m_pick.setColor(sf::Color(153, 153, 255, 255));
	m_pick.setCharacterSize(REG_CHAR_SIZE);
	m_pick.setPosition({ SCREEN_CENTER.x - 720 , SCREEN_CENTER.y - 200 });
	m_pick.setString("Pick a Character:");
	m_pick.setOutlineColor(sf::Color::Black);
	m_pick.setOutlineThickness(OUTLINE_THICKNESS);
	
}
//--------------------------------------------------
//set the Players details

void MenuScreen::setPlayer()
{
	auto m_pTexture = FileManager::instance().getPlayerTexture();

	m_boyplayer.setTexture(m_pTexture);
	m_boyplayer.setTextureRect(FileManager::instance().getPlayerRect(MALE));
	m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);
	m_boyplayer.setOutlineColor(sf::Color::Black);
	m_boyplayer.setPosition({ SCREEN_CENTER.x - 400 , SCREEN_CENTER.y - 60 });
	m_boyplayer.setSize({ BLOCK_SIZE * 4, BLOCK_SIZE * 4 });

	m_girlplayer.setTexture(m_pTexture);
	m_girlplayer.setTextureRect(FileManager::instance().getPlayerRect(FEMALE));
	m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);
	m_girlplayer.setOutlineColor(sf::Color::Black);
	m_girlplayer.setPosition({ SCREEN_CENTER.x - 700 , SCREEN_CENTER.y - 60 });
	m_girlplayer.setSize({ BLOCK_SIZE*4, BLOCK_SIZE*4 });
}
//------------------------------------------------
//draw all the buttons on the window

void MenuScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_start);
	window.draw(this->m_exit);
	window.draw(this->m_boyplayer);
	window.draw(this->m_girlplayer);
	window.draw(this->m_help);
	window.draw(this->m_pick);

	window.display();
}
//--------------------------------------------------
//handle click on the menu buttons

screensOption MenuScreen::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window)
{
	//m_pick
	if (this->m_start.getGlobalBounds().contains(Location)) // pressed start
	{
		if (m_selectedPlayer != WAIT)
		{
			playSelectSound();
			return START;
		}
		this->m_pick.setOutlineColor(sf::Color::Red);
		this->m_pick.setOutlineThickness(BOLD_OUTLINE);
	}
	
	if (this->m_help.getGlobalBounds().contains(Location)) // pressed help
	{
		playSelectSound();
		return HELP;
	}
	if (this->m_girlplayer.getGlobalBounds().contains(Location)) // pressed help
	{
		playSelectSound();
		m_selectedPlayer = FEMALE;
		this->m_girlplayer.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_girlplayer.setOutlineThickness(BOLD_OUTLINE);
		this->m_boyplayer.setOutlineColor(sf::Color::Black);
		this->m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);

	}
	if (this->m_boyplayer.getGlobalBounds().contains(Location)) // pressed help
	{
		playSelectSound();
		m_selectedPlayer = MALE;
		this->m_boyplayer.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_boyplayer.setOutlineThickness(BOLD_OUTLINE);
		this->m_girlplayer.setOutlineColor(sf::Color::Black);
		this->m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);

	}
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		playSelectSound();
		window.close();
	}
		// pressed exit
	
	return NONE;
}

//--------------------------------------------------
//handle moving on the menu buttons

void MenuScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
	if (this->m_start.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_start.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_start.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_start.setOutlineColor(sf::Color::Black);
		this->m_start.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_exit.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(sf::Color::Black);
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark help button
	if (this->m_help.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_help.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_help.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_help.setOutlineColor(sf::Color::Black);
		this->m_help.setOutlineThickness(OUTLINE_THICKNESS);
	}

	if (this->m_boyplayer.getOutlineColor() != sf::Color(0, 0, 77, 255))
	{
		// mark/unmark help button
		if (this->m_boyplayer.getGlobalBounds().contains(Location))
		{
			playMoveSound();
			this->m_boyplayer.setOutlineColor(sf::Color(230, 230, 255, 255));
			this->m_boyplayer.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{

			this->m_boyplayer.setOutlineColor(sf::Color::Black);
			this->m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);

		}
	}
	if (this->m_girlplayer.getOutlineColor() != sf::Color(0, 0, 77, 255))
	{
		// mark/unmark help button
		if (this->m_girlplayer.getGlobalBounds().contains(Location))
		{
			playMoveSound();
			this->m_girlplayer.setOutlineColor(sf::Color(230, 230, 255, 255));
			this->m_girlplayer.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{

			this->m_girlplayer.setOutlineColor(sf::Color::Black);
			this->m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);

		}
	}
	this->m_pick.setOutlineColor(sf::Color::Black);
	this->m_pick.setOutlineThickness(OUTLINE_THICKNESS);
}
