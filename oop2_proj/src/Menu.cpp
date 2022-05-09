#pragma warning (disable : 4996)
#include "Menu.h"
#include "Macros.h"
#include <iostream>

//--------------------------------------------------
//constructor

Menu::Menu()
	:m_pressStart(false), m_pressHelp(false)
{
	this->m_font=(*(FileManager::p2FileManager().getFont()));

	setHeader();
	setStart();
	setExit();
	setHelp();

	this->m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_background.setTexture(FileManager::p2FileManager().getBackGround(MENU_BACKGROUND));
}
//--------------------------------------------------
//set the header details

void Menu::setHeader()
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

void Menu::setStart()
{
	m_start.setFont(m_font);
	m_start.setColor(sf::Color(153, 153, 255, 255));
	m_start.setCharacterSize(REG_CHAR_SIZE);
	m_start.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y - 70 });
	m_start.setString("Start");
	m_start.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_start.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//set the help details

void Menu::setHelp()
{
	m_help.setFont(m_font);
	m_help.setColor(sf::Color(153, 153, 255, 255));
	m_help.setCharacterSize(REG_CHAR_SIZE);
	m_help.setPosition({ SCREEN_CENTER.x - 40, SCREEN_CENTER.y + 190 });
	m_help.setString("Help");
	m_help.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_help.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//set the exit details

void Menu::setExit()
{
	m_exit.setFont(m_font);
	m_exit.setColor(sf::Color(153, 153, 255, 255));
	m_exit.setCharacterSize(REG_CHAR_SIZE);
	m_exit.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
	m_exit.setOutlineColor(sf::Color(230, 230, 255, 255));
	m_exit.setOutlineThickness(OUTLINE_THICKNESS);
}
//--------------------------------------------------
//start the menu screen

void Menu::activateMenuScreen(sf::RenderWindow& window)
{
	m_pressStart = false;
	m_pressHelp = false;

	while (window.isOpen())
	{
		draw(window);
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			sf::Vector2f Location;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				Location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (handleClick(Location, window))
				{
					if(m_pressStart)
					return;
					if (m_pressHelp)
					{
						helpWindow(window);
						return;
					}
				}
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}
}
//------------------------------------------------
//draw all the buttons on the window

void Menu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_start);
	window.draw(this->m_exit);
	window.draw(this->m_help);
	window.display();
}
//--------------------------------------------------
//handle click on the menu buttons

bool Menu::handleClick(const sf::Vector2f& Location, sf::RenderWindow& window) 
{
	if (this->m_start.getGlobalBounds().contains(Location)) // pressed start
	{
		m_pressStart=true;
		return true;
	}
	
	if (this->m_help.getGlobalBounds().contains(Location)) // pressed help
	{
	   m_pressHelp=true;
		return true;
	}
	if (this->m_exit.getGlobalBounds().contains(Location)) // pressed exit
		window.close();
	return false;
}
//--------------------------------------------------
//handle moving on the menu buttons

void Menu::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
	if (this->m_start.getGlobalBounds().contains(Location))
	{
		this->m_start.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_start.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_start.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_start.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		this->m_exit.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark help button
	if (this->m_help.getGlobalBounds().contains(Location))
	{
		this->m_help.setOutlineColor(sf::Color(0, 0, 77, 255));
		this->m_help.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_help.setOutlineColor(sf::Color(230, 230, 255, 255));
		this->m_help.setOutlineThickness(OUTLINE_THICKNESS);
	}
}
//-----------------------------------------------------------------

void Menu::helpWindow(sf::RenderWindow& window)
{
	setHelpWindow(window);

	while (window.isOpen())
	{
		drawHelp(window);
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			sf::Vector2f Location;
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				Location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (handleClick(Location, window))
				{
					m_start.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y - 70 });
					m_exit.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y + 60 });
					return;
				}
				break;
			case sf::Event::MouseMoved:
				Location = (sf::Vector2f)sf::Mouse::getPosition(window);
				handleMove(Location);
				break;
			}
		}
	}
}
//------------------------------------------------
void Menu::drawHelp(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_helpBackground);
	window.draw(this->m_header);
	window.draw(this->m_start);
	window.draw(this->m_exit);
	window.display();
}
//------------------------------------------------

void Menu::setHelpWindow(sf::RenderWindow& window)
{

	m_exit.setPosition({ WINDOW_WIDTH-155  , WINDOW_HEIGHT- BUFF_DISTANCE });
	m_start.setPosition({ 20,  WINDOW_HEIGHT- BUFF_DISTANCE });

	this->m_helpBackground.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	this->m_helpBackground.setTexture(FileManager::p2FileManager().getBackGround(HELP_BACKGROUND));
}