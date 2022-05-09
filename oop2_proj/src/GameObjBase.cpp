#include "GameObjBase.h"

#include <SFML/Graphics.hpp>

//--------------------------------------------------
//constructor

GameObjBase::GameObjBase(icons icon, int i, int j)
{
	auto m_pTexture = FileManager::p2FileManager().getIconTexture(icon);
	m_sprite.setTexture(*m_pTexture);
	m_sprite.setPosition(sf::Vector2f(i * (float)P_SIZE, j * (float)P_SIZE));
}
//-----------------------------------------------
//draw the sprite on the window

void GameObjBase::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//--------------------------------------------------
//get the scale of the sprite

sf::Vector2f GameObjBase::getScale() const
{
	return m_sprite.getScale();
}
//--------------------------------------------------
//get the position of the sprite

sf::Vector2f GameObjBase::getPos() const
{
	return m_sprite.getPosition();
}
//--------------------------------------------------
//set the position of the sprite

void GameObjBase::setPos(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}
//--------------------------------------------------
//get the width of the sprite

float GameObjBase::getIconWidth() const
{
	return m_sprite.getGlobalBounds().width;
}
//--------------------------------------------------
//get the height of the sprite

float GameObjBase::getIconHeight() const
{
	return m_sprite.getGlobalBounds().height;
}
//--------------------------------------------------

bool GameObjBase::checkCollision(const GameObjBase& obj)
{
	if(&obj)
	return m_sprite.getGlobalBounds().intersects(obj.m_sprite.getGlobalBounds());

	return false;
}

