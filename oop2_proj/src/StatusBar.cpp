#pragma once
#include "StatusBar.h"
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

StatusBar::StatusBar() : m_level(0)
{
	this->m_font = (*(FileManager::instance().getFont()));

	setCurrPowerRect();
	setCurrLifeRect();
	setDiamondCounter();
	setLevelText();
	setMusicIcon();
	setStopIcon();
	//setRestartIcon();
}
//------------------------------------------

void StatusBar::updateLevel(const bool isLevelUp)
{	
	if (isLevelUp)
		this->m_level++;

	this->m_levelText.setString("Level :" + std::to_string(this->m_level));
}
//------------------------------------------

int StatusBar::getLevel() const
{
	return this->m_level;
}
//------------------------------------------

void StatusBar::setLevel(const int lev)
{
	 this->m_level= lev;
}
//------------------------------------------

void StatusBar::updatePos(const sf::Vector2f center)
{
	m_lifeFrame.setPosition(center.x + 125, center.y - 115);
	m_currLife.setPosition(center.x +125, center.y - 115);
	m_lifeIcon.setPosition(center.x + 110, center.y - 115);

	m_powerFrame.setPosition(center.x + 125, center.y - 100);
	m_currPower.setPosition(center.x + 125, center.y - 100);
	m_powerIcon.setPosition(center.x + 112, center.y - 101);

	m_diamondText.setPosition(center.x + 125, center.y - 88);
	m_diamondIcon.setPosition(center.x + 110, center.y - 85);

	this->m_levelText.setPosition(center.x-170, center.y - 110);
	this->m_musicIcon.setPosition(center.x - 170, center.y - 90);
	this->m_stopAndPlayIcon.setPosition(center.x -160, center.y - 90);
}
//------------------------------------------

void StatusBar::draw(sf::RenderWindow& window,const int power,
	const int life,const int currDiamonds)
{
	updateDiamondText(currDiamonds);
	updateLifeAndPower(power, life);

	window.draw(this->m_diamondText);
	window.draw(this->m_diamondIcon);
	window.draw(this->m_currLife);
	window.draw(this->m_currPower); 
	window.draw(this->m_powerFrame);
	window.draw(this->m_lifeFrame);
	window.draw(this->m_powerIcon);
	window.draw(this->m_lifeIcon);
	window.draw(this->m_levelText);
	window.draw(this->m_musicIcon);
	window.draw(this->m_stopAndPlayIcon);
	//window.draw(this->m_resetIcon);
}
//------------------------------------------

void StatusBar::updateLifeAndPower(const int power, const int life)
{
	m_currPower.setSize(sf::Vector2f(power * 0.05, m_currPower.getSize().y));
	m_currLife.setSize(sf::Vector2f(life * 0.05, m_currLife.getSize().y));
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

void StatusBar::setStopAndPlayIcon(const bool ToPlay)
{
	this->m_stopAndPlayIcon.setTexture(*FileManager::instance().getPlayAndStopIcon(ToPlay));
}
//------------------------------------------

bool StatusBar::containsMusicIcon(const sf::Event& event) const
{
	std::cout << "me" << event.mouseButton.x << " " << event.mouseButton.y << "\n";
	std::cout << "music" << m_musicIcon.getPosition().x << " " << m_musicIcon.getPosition().y << "\n";
	if (this->m_musicIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//------------------------------------------

void StatusBar::setMusicIcon(const bool isSoundOn)
{
	this->m_musicIcon.setTexture(*FileManager::instance().getMusicIcon(isSoundOn));
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
	this->m_levelText.setFont(*FileManager::instance().getFont());
	this->m_levelText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_levelText.setColor(sf::Color(153, 153, 255, 255));
	this->m_levelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_levelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setDiamondCounter()
{
	this->m_diamondText.setFont(*FileManager::instance().getFont());
	this->m_diamondText.setCharacterSize(STATUS_BAR_CHAR_SIZE-1);
	this->m_diamondText.setFillColor(sf::Color::White);
	this->m_diamondText.setOutlineThickness(0.5);
	this->m_diamondText.setOutlineColor(sf::Color::White);

	m_diamondIcon.setTexture(*FileManager::instance().getBIcons(B_DIAMOND));
	m_diamondIcon.scale(MUSIC_ICON_SCALE*6.f);
}
//--------------------------------------------

void StatusBar::setMusicIcon()
{
	this->m_musicIcon.setTexture(*FileManager::instance().getMusicIcon(true));
	this->m_musicIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setStopIcon()
{
	this->m_stopAndPlayIcon.setTexture(*FileManager::instance().getPlayAndStopIcon(true));
	this->m_stopAndPlayIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setRestartIcon()
{
	this->m_resetIcon.setTexture(*FileManager::instance().getRestartIcon());
	this->m_resetIcon.scale(MUSIC_ICON_SCALE);
}
//--------------------------------------------

void StatusBar::setCurrLifeRect()
{
	m_lifeFrame.setFillColor(sf::Color::Transparent);
	m_lifeFrame.setOutlineColor(sf::Color::Black);
	m_lifeFrame.setSize(sf::Vector2f(50.f, 8.f));
	m_lifeFrame.setOutlineThickness(1.5);

	m_currLife.setFillColor(sf::Color::Red);
	m_currLife.setSize(sf::Vector2f(50.f, 8.f));

	m_lifeIcon.setTexture(*FileManager::instance().getBIcons(B_LIFE));
	m_lifeIcon.scale(MUSIC_ICON_SCALE* 4.f);

}
//--------------------------------------------

void StatusBar::setCurrPowerRect()
{
	m_powerFrame.setFillColor(sf::Color::Transparent);
	m_powerFrame.setOutlineColor(sf::Color::Black);
	m_powerFrame.setOutlineThickness(1.5);
	m_powerFrame.setSize(sf::Vector2f(50.f, 8.f));

	m_powerIcon.setTexture(*FileManager::instance().getBIcons(B_POWER));
	m_powerIcon.scale(MUSIC_ICON_SCALE*1.5f);

	m_currPower.setFillColor(sf::Color::Yellow);
	m_currPower.setSize(sf::Vector2f(50.f, 8.f));
}