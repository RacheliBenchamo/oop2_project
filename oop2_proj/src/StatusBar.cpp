#pragma once
#include "StatusBar.h"
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

StatusBar::StatusBar() : m_level(0), m_minutes(0), m_seconds(0)
{
	this->m_font = (*(FileManager::p2FileManager().getFont()));

	//setCurrPlayerText();
	setCurrPowerRect();
	setCurrLifeRect();
	setDiamondCounter();
	setLevelText();
	setTimeText();
	setMusicIcon();
	setStopIcon();
	//setRestartIcon();
}
//------------------------------------------

void StatusBar::updateTime()
{
		this->m_seconds += this->m_timer.getElapsedTime().asSeconds();
		if (m_seconds >= 60)
		{
			this->m_seconds = 0;
			this->m_minutes++;
		}
		updateTimePassText();
		resetTimer();
}
//------------------------------------------

void StatusBar::updateTimePassText()
{
	if (m_seconds >= 10 && m_minutes < 10)
		this->m_timeText.setString(" Time Pass :0" + std::to_string((int)this->m_minutes)
			+ ":" + std::to_string((int)this->m_seconds));
	else if (m_seconds >= 10 && m_minutes >= 10)
		this->m_timeText.setString(" Time Pass :" + std::to_string((int)this->m_minutes)
			+ ":" + std::to_string((int)this->m_seconds));
	else if (m_seconds < 10 && m_minutes >= 10)
		this->m_timeText.setString(" Time Pass :" + std::to_string((int)this->m_minutes)
			+ ":0" + std::to_string((int)this->m_seconds));
	else
		this->m_timeText.setString(" Time Pass :0" + std::to_string((int)this->m_minutes)
			+ ":0" + std::to_string((int)this->m_seconds));
}
//------------------------------------------

void StatusBar::updateLevel( bool isLevelUp)
{

	setTime(0);
	
	if (isLevelUp)
		this->m_level++;

	this->m_levelText.setString("Level :" + std::to_string(this->m_level));
	resetTimer();
}
//------------------------------------------

int StatusBar::getLevel() const
{
	return this->m_level;
}
//------------------------------------------

void StatusBar::setLevel(int lev)
{
	 this->m_level= lev;
}
//------------------------------------------

float StatusBar::getTime() const
{
		return 1;
}
//------------------------------------------

void StatusBar::resetTimer()
{
	m_timer.restart();
}
//------------------------------------------

void StatusBar::setTime(int time)
{
	m_minutes = time/60;
	m_seconds = time % 60;
}
//------------------------------------------

void StatusBar::updatePos(sf::Vector2f center)
{
	m_currLife.setPosition(center.x +125, center.y - 115);
	m_lifeIcon.setPosition(center.x + 120, center.y - 114);

	m_currPower.setPosition(center.x + 125, center.y - 105);
	m_powerIcon.setPosition(center.x + 120, center.y - 104);

	m_diamondText.setPosition(center.x + 130, center.y - 95);
	m_diamondIcon.setPosition(center.x + 120, center.y - 93);

	this->m_levelText.setPosition(center.x-170, center.y - 110);
	//this->m_timeText.setPosition(center.x - 170, center.y - 100);
	this->m_musicIcon.setPosition(center.x - 170, center.y - 90);
	this->m_stopAndPlayIcon.setPosition(center.x -160, center.y - 90);
}
//------------------------------------------

void StatusBar::draw(sf::RenderWindow& window,const int power,const int life,const int currDiamonds)
{
	updateTime();
	updateDiamondText(currDiamonds);
	updateLifeAndPower(power, life);

	window.draw(this->m_diamondText);
	window.draw(this->m_diamondIcon);

	window.draw(this->m_currLife);
	window.draw(this->m_currPower);

	window.draw(this->m_powerIcon);
	window.draw(this->m_lifeIcon);

	window.draw(this->m_levelText);
	window.draw(this->m_musicIcon);
	window.draw(this->m_stopAndPlayIcon);
	//std::cout<<""
	//window.draw(this->m_resetIcon);
	//window.draw(this->m_timeText);

}
//------------------------------------------

void StatusBar::updateLifeAndPower(int power, int life)
{
	m_currPower.setSize(sf::Vector2f(power * 0.5, m_currPower.getSize().y));
	m_currLife.setSize(sf::Vector2f(life * 0.5, m_currLife.getSize().y));

}
//------------------------------------------

void StatusBar::updateDiamondText(const int currDiamonds)
{
	this->m_diamondText.setString(std::to_string(currDiamonds)+ " / " + std::to_string(m_maxDiamonds));
}
//------------------------------------------

void StatusBar::resetNumOfLevel()
{
	m_level = 0;
}
//------------------------------------------

bool StatusBar::containsStopAndPlayIcon(const sf::Event& event) const
{
	if (this->m_stopAndPlayIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//------------------------------------------

void StatusBar::setStopAndPlayIcon(bool ToPlay)
{
	this->m_stopAndPlayIcon.setTexture(*FileManager::p2FileManager().getPlayAndStopIcon(ToPlay));
}
//------------------------------------------

bool StatusBar::containsMusicIcon(const sf::Event& event) const
{
	if (this->m_musicIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//------------------------------------------

void StatusBar::setMusicIcon(bool isSoundOn)
{
	this->m_musicIcon.setTexture(*FileManager::p2FileManager().getMusicIcon(isSoundOn));
}
//------------------------------------------

bool StatusBar::containsRestartIcon(const sf::Event& event) const
{
	if (this->m_resetIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//--------------------------------------------

void StatusBar::setLevelText()
{
	this->m_levelText.setFont(*FileManager::p2FileManager().getFont());
	this->m_levelText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	//this->m_levelText.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT - BUFF_DISTANCE);
	this->m_levelText.setColor(sf::Color(153, 153, 255, 255));
	this->m_levelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_levelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setTimeText()
{
	this->m_timeText.setFont(*FileManager::p2FileManager().getFont());
	this->m_timeText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	//this->m_timeText.setPosition(WINDOW_WIDTH / 2.5, WINDOW_HEIGHT - BUFF_DISTANCE);
	this->m_timeText.setColor(sf::Color(153, 153, 255, 255));
	this->m_timeText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_timeText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setDiamondCounter()
{
	this->m_diamondText.setFont(*FileManager::p2FileManager().getFont());
	this->m_diamondText.setCharacterSize(STATUS_BAR_CHAR_SIZE-2);
	this->m_diamondText.setColor(sf::Color(230, 230, 255, 255));
	//this->m_diamondText.setOutlineColor(sf::Color(230, 230, 255, 255));
	//this->m_diamondText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);

	m_diamondIcon.setTexture(*FileManager::p2FileManager().getBIcons(B_DIAMOND));
	m_diamondIcon.scale(MUSIC_ICON_SCALE*3.f);
}
//--------------------------------------------

void StatusBar::setMusicIcon()
{
	this->m_musicIcon.setTexture(*FileManager::p2FileManager().getMusicIcon(true));
	//this->m_musicIcon.setPosition(WINDOW_WIDTH/1.3, WINDOW_HEIGHT - BUFF_DISTANCE/2);
	this->m_musicIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setStopIcon()
{
	this->m_stopAndPlayIcon.setTexture(*FileManager::p2FileManager().getPlayAndStopIcon(true));
	//this->m_stopAndPlayIcon.setPosition(WINDOW_WIDTH/ 1.19, WINDOW_HEIGHT - BUFF_DISTANCE / 2);
	this->m_stopAndPlayIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setRestartIcon()
{
	this->m_resetIcon.setTexture(*FileManager::p2FileManager().getRestartIcon());
	//this->m_resetIcon.setPosition(WINDOW_WIDTH/1.1 , WINDOW_HEIGHT - BUFF_DISTANCE / 2);
	this->m_resetIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setCurrLifeRect()
{
	m_currLife.setFillColor(sf::Color::Green);
	m_currLife.setSize(sf::Vector2f(50.f, 8.f));

	m_lifeIcon.setTexture(*FileManager::p2FileManager().getBIcons(B_LIFE));
	m_lifeIcon.scale(MUSIC_ICON_SCALE* 2.f);

}
//--------------------------------------------

void StatusBar::setCurrPowerRect()
{
	m_powerIcon.setTexture(*FileManager::p2FileManager().getBIcons(B_POWER));
	m_powerIcon.scale(MUSIC_ICON_SCALE);

	m_currPower.setFillColor(sf::Color::Yellow);
	m_currPower.setSize(sf::Vector2f(50.f, 8.f));
}