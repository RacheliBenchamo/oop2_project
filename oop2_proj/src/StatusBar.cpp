#pragma once
#include "StatusBar.h"
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

StatusBar::StatusBar() : m_level(0), m_minutes(0), m_seconds(0), m_timelessLevel(false)
{
	this->m_font = (*(FileManager::p2FileManager().getFont()));

	setCurrPlayerText();
	setLevelText();
	setTimeText();
	setMusicIcon();
	setStopIcon();
	setRestartIcon();
}
//------------------------------------------

void StatusBar::updateTime()
{

	if (!m_timelessLevel)
	{
		this->m_seconds -= this->m_timer.getElapsedTime().asSeconds();
		if (m_seconds <= 0 && m_minutes > 0)
		{
			m_seconds = 59;
			m_minutes--;
		}
		updateTimeLeftText();
		this->m_timer.restart();
	}
	else
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

void StatusBar::updateTimeLeftText()
{
	if (m_seconds >= 10 && m_minutes < 10)
		this->m_timeText.setString(" Time Left :0" + std::to_string((int)this->m_minutes)
			+ ":" + std::to_string((int)this->m_seconds));
	else if (m_seconds >= 10 && m_minutes >= 10)
		this->m_timeText.setString(" Time Left :" + std::to_string((int)this->m_minutes)
			+ ":" + std::to_string((int)this->m_seconds));
	else if (m_seconds < 10 && m_minutes >= 10)
		this->m_timeText.setString(" Time Left :" + std::to_string((int)this->m_minutes)
			+ ":0" + std::to_string((int)this->m_seconds));
	else
		this->m_timeText.setString(" Time Left :0" + std::to_string((int)this->m_minutes)
			+ ":0" + std::to_string((int)this->m_seconds));
}
//------------------------------------------

void StatusBar::updateLevel(int time, bool isLevelUp)
{
	if (time == 0) //if its a timeless level
	{
		m_timelessLevel = true;
		setTime(0);
	}
	else
	{
		m_timelessLevel = false;
		setTime(time);
	}
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
	if (m_timelessLevel)
		return 1;

	return (m_minutes*60+ m_seconds);
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
void StatusBar::draw(sf::RenderWindow& window, int currPlayer)
{
	updateTime();
	window.draw(this->m_playersSprite[currPlayer]);
	window.draw(this->m_currPlayerText);
	window.draw(this->m_levelText);
	window.draw(this->m_timeText);
	window.draw(this->m_musicIcon);
	window.draw(this->m_stopAndPlayIcon);
	window.draw(this->m_resetIcon);
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
//------------------------------------------

void StatusBar::currPlayerDetail()
{
	this->m_playersSprite[KING].setTexture(*FileManager::p2FileManager().getIconTexture(KING));
	this->m_playersSprite[WARRIOR].setTexture(*FileManager::p2FileManager().getIconTexture(WARRIOR));
	this->m_playersSprite[THIEF].setTexture(*FileManager::p2FileManager().getIconTexture(THIEF));
	this->m_playersSprite[MAGE].setTexture(*FileManager::p2FileManager().getIconTexture(MAGE));

	for (int i = 0; i < NUM_OF_PLAYERS; i++)
	{
		this->m_playersSprite[i].setPosition(WINDOW_WIDTH / 5.5, WINDOW_HEIGHT - BUFF_DISTANCE / 2);
		this->m_playersSprite[i].setTextureRect(sf::IntRect(32, 0 * 32, 32, 32));
		this->m_playersSprite[i].setScale(1.8, 1.8);
	}
}
//--------------------------------------------
void StatusBar::setCurrPlayerText()
{
	currPlayerDetail();

	this->m_currPlayerText.setFont(*FileManager::p2FileManager().getFont());
	this->m_currPlayerText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_currPlayerText.setPosition(100, WINDOW_HEIGHT - BUFF_DISTANCE);
	this->m_currPlayerText.setColor(sf::Color(153, 153, 255, 255));
	this->m_currPlayerText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_currPlayerText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
	this->m_currPlayerText.setString("Player :");
}
//--------------------------------------------

void StatusBar::setLevelText()
{
	this->m_levelText.setFont(*FileManager::p2FileManager().getFont());
	this->m_levelText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_levelText.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT - BUFF_DISTANCE);
	this->m_levelText.setColor(sf::Color(153, 153, 255, 255));
	this->m_levelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_levelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setTimeText()
{
	this->m_timeText.setFont(*FileManager::p2FileManager().getFont());
	this->m_timeText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_timeText.setPosition(WINDOW_WIDTH / 2.5, WINDOW_HEIGHT - BUFF_DISTANCE);
	this->m_timeText.setColor(sf::Color(153, 153, 255, 255));
	this->m_timeText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_timeText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setMusicIcon()
{
	this->m_musicIcon.setTexture(*FileManager::p2FileManager().getMusicIcon(true));
	this->m_musicIcon.setPosition(WINDOW_WIDTH/1.3, WINDOW_HEIGHT - BUFF_DISTANCE/2);
	this->m_musicIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setStopIcon()
{
	this->m_stopAndPlayIcon.setTexture(*FileManager::p2FileManager().getPlayAndStopIcon(true));
	this->m_stopAndPlayIcon.setPosition(WINDOW_WIDTH/ 1.19, WINDOW_HEIGHT - BUFF_DISTANCE / 2);
	this->m_stopAndPlayIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setRestartIcon()
{
	this->m_resetIcon.setTexture(*FileManager::p2FileManager().getRestartIcon());
	this->m_resetIcon.setPosition(WINDOW_WIDTH/1.1 , WINDOW_HEIGHT - BUFF_DISTANCE / 2);
	this->m_resetIcon.scale(MUSIC_ICON_SCALE);
}
