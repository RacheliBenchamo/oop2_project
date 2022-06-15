#pragma once
#include "StatusBar.h"
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

StatusBar::StatusBar()
{
	m_font = (*(FileManager::instance().getFont()));

	setCurrPowerRect();
	setCurrLifeRect();
	setDiamondCounter();
	setIcons();
}
//--------------------------------------------------

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

	m_musicIcon.setPosition(center.x - 175, center.y - 115);
	m_soundIcon.setPosition(center.x - 160, center.y - 115);
	m_stopAndPlayIcon.setPosition(center.x - 145, center.y - 115);
	m_resetIcon.setPosition(center.x - 130, center.y - 115);
}
//--------------------------------------------------
//change music icon

void StatusBar::changeMusicIcon()
{
	m_musicIcon.getTextureRect() == P_MUSIC_ON ?
		m_musicIcon.setTextureRect(P_MUSIC_OFF) :
		m_musicIcon.setTextureRect(P_MUSIC_ON);
}
//--------------------------------------------------
//change play icon

void StatusBar::changePlayIcon()
{
	m_stopAndPlayIcon.getTextureRect() == P_PLAY_ICON ?
		m_stopAndPlayIcon.setTextureRect(P_STOP_ICON) :
		m_stopAndPlayIcon.setTextureRect(P_PLAY_ICON);
}
//--------------------------------------------------
//change sound icon

void StatusBar::changeSoundIcon()
{
	m_soundIcon.getTextureRect() == P_SOUND_ON ?
		m_soundIcon.setTextureRect(P_SOUND_OFF) :
		m_soundIcon.setTextureRect(P_SOUND_ON);
}
//--------------------------------------------------
//draw 

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
	drawIcons(window);
}
//--------------------------------------------------
//update Life And Power

void StatusBar::updateLifeAndPower(const int power, const int life)
{
	m_currPower.setSize(sf::Vector2f(power * 0.05, m_currPower.getSize().y));
	m_currLife.setSize(sf::Vector2f(life * 0.05, m_currLife.getSize().y));
}
//--------------------------------------------------
//draw icons

void StatusBar::drawIcons(sf::RenderWindow& window)
{
	window.draw(this->m_musicIcon);
	window.draw(this->m_stopAndPlayIcon);
	window.draw(this->m_resetIcon);
	window.draw(this->m_soundIcon);
}
//--------------------------------------------------
//update diamond text

void StatusBar::updateDiamondText(const int currDiamonds)
{
	this->m_diamondText.setString(std::to_string(currDiamonds)+ " / " + std::to_string(m_maxDiamonds));
}
//--------------------------------------------------
//set icons

void StatusBar::setIcons()
{
	auto m_pTexture = FileManager::instance().getIconsTexture();
	m_musicIcon.setTexture(*m_pTexture);
	m_resetIcon.setTexture(*m_pTexture);
	m_stopAndPlayIcon.setTexture(*m_pTexture);
	m_soundIcon.setTexture(*m_pTexture);

	m_musicIcon.setTextureRect(P_MUSIC_ON);
	m_resetIcon.setTextureRect(P_RESTART_ICON);
	m_stopAndPlayIcon.setTextureRect(P_STOP_ICON);
	m_soundIcon.setTextureRect(P_SOUND_ON);

	m_musicIcon.scale(MUSIC_ICON_SCALE * 15.f);
	m_resetIcon.scale(MUSIC_ICON_SCALE * 15.f);
	m_stopAndPlayIcon.scale(MUSIC_ICON_SCALE * 15.f);
	m_soundIcon.scale(MUSIC_ICON_SCALE * 15.f);
}
//--------------------------------------------------

bool StatusBar::containsStopAndPlayIcon(const sf::Vector2f pos) const
{
	if (m_stopAndPlayIcon.getGlobalBounds().contains(pos.x, pos.y))
		return true;
	return false;
}
//--------------------------------------------------

bool StatusBar::containsMusicIcon(const sf::Vector2f pos) const
{
	if (m_musicIcon.getGlobalBounds().contains(pos.x, pos.y))
		return true;
	return false;
}
//--------------------------------------------------

bool StatusBar::containsRestartIcon(const sf::Vector2f pos) const
{
	if (m_resetIcon.getGlobalBounds().contains(pos.x , pos.y))
		return true;
	return false;
}
//--------------------------------------------------

bool StatusBar::containsSoundIcon(const sf::Vector2f pos) const
{
	if (m_soundIcon.getGlobalBounds().contains(pos.x , pos.y))
		return true;
	return false;
}  
//--------------------------------------------------
//set diamond counter

void StatusBar::setDiamondCounter()
{
	m_diamondText.setFont(*FileManager::instance().getFont());
	m_diamondText.setCharacterSize(STATUS_BAR_CHAR_SIZE-1);
	m_diamondText.setFillColor(sf::Color::White);
	m_diamondText.setOutlineThickness(0.5);
	m_diamondText.setOutlineColor(sf::Color::White);

	m_diamondIcon.setTexture(*FileManager::instance().getBIcons(B_DIAMOND));
	m_diamondIcon.scale(MUSIC_ICON_SCALE*6.f);
}
//--------------------------------------------------

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
//--------------------------------------------------

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