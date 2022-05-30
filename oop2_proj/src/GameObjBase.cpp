#include "GameObjBase.h"

#include <SFML/Graphics.hpp>

//--------------------------------------------------
//constructor

GameObjBase::GameObjBase(const sf::Vector2f& size, const sf::Vector2f& pos)
{
	m_shape.setScale(1, 1);
	m_shape.setPosition(pos);
	m_shape.setSize(size);
	m_shape.setOrigin(sf::Vector2f({ size.x / 2,size.y / 2 }));
}
//-----------------------------------------------
//draw the sprite on the window

void GameObjBase::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}
//--------------------------------------------------
//get the scale of the sprite

sf::Vector2f GameObjBase::getScale() const
{
	return m_shape.getScale();
}
//--------------------------------------------------
//get the position of the sprite

sf::Vector2f GameObjBase::getPos() const
{
	return m_shape.getPosition();
}
//--------------------------------------------------
//set the position of the sprite

void GameObjBase::setPos(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}


void GameObjBase::setToDelete()
{
	m_delete = true;
}
//--------------------------------------------------

bool GameObjBase::getToReplace() const
{
	return m_replace;
}
//--------------------------------------------------

void GameObjBase::setToReplace()
{
	m_replace = true;
}
//--------------------------------------------------

//bool GameObjBase::getToReplace()const
//{
//	return m_replace;
//}
////--------------------------------------------------
//
//void GameObjBase::setReplace()
//{
//	m_replace = true;
//}
//--------------------------------------------------

bool GameObjBase::getToDelete()const
{
	return m_delete;
}

//--------------------------------------------------
//get the width of the sprite

float GameObjBase::getIconWidth() const
{
	return m_shape.getGlobalBounds().width;
}
//--------------------------------------------------
//get the height of the sprite

float GameObjBase::getIconHeight() const
{
	return m_shape.getGlobalBounds().height;
}
//--------------------------------------------------

bool GameObjBase::checkCollision(const GameObjBase& obj)
{
	if (&obj)
		if (m_shape.getGlobalBounds().intersects(obj.m_shape.getGlobalBounds()))
			return true;
			

	return false;
}

//---------------------------- setDisappear ------------------------------
// Update that the object should disappear.
//------------------------------------------------------------------------
void GameObjBase::setDisappear(bool status)
{
	m_disappear = status;
}
