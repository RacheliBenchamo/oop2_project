#include "MovingInclude\\MovingObj.h"
#include "Macros.h"

//------------------------------------------
//set the sprite pos to her prev pos

void MovingObj::backToPrevPos()
{
	setPos(m_prevPos);
}
//------------------------------------------
//return true if the sprite pos is out od the window
//else,return false

bool MovingObj::outWindow(sf::Vector2f pos, sf::Vector2f levelSize) const
{
	if (pos.x <= START_SPACE*1.5 ||
		pos.y >= (levelSize.x * X_SPACE) - START_SPACE /3.2||
		pos.x >= (levelSize.y * Y_SPACE) + START_SPACE*3.5)
			return true;
	
	    return false;
}
//------------------------------------------
//update the animation of the charcter by 
//the direction it goes to

void MovingObj::updateAnimation()
{
	if (m_currDirection == DVec[DOWN])
	{
		m_animationRow = 0;
		updateSpriteCol();
	}
	else if (m_currDirection == DVec[LEFT])
	{
		m_animationRow = 1;
		updateSpriteCol();
	}
	else if (m_currDirection == DVec[RIGHT])
	{
		m_animationRow = 2;
		updateSpriteCol();
	}
	else if (m_currDirection == DVec[UP])
	{
		m_animationRow = 3;
		updateSpriteCol();
	}
}
//------------------------------------------------------------
//update the col in the sprite pic to create run affect

void MovingObj::updateSpriteCol()
{
	sf::RectangleShape shape = getShape();

	if (m_animationCol == 2)
		m_animationCol = 0;
	else
		m_animationCol++;

	shape.setTextureRect(sf::IntRect(m_animationCol * 32, m_animationRow * 32, 32, 32));
	setShape(shape);
}
//------------------------------------------
//return the right direction by which key pressed

sf::Vector2f MovingObj::getDirection() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return RIGHT_MOVEMENT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return LEFT_MOVEMENT;

	return STAY_IN_PLACE;
}