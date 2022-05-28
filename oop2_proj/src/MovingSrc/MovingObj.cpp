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
	if (pos.x <= START_SPACE*1.5 || pos.y <= -10||
		pos.y >= (levelSize.x * X_SPACE) - START_SPACE /3.2||
		pos.x >= (levelSize.y * Y_SPACE) + START_SPACE*3.5)
			return true;
	
	    return false;
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