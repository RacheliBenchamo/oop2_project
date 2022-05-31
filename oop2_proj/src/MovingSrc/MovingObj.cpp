#include "MovingInclude\\MovingObj.h"
#include "Macros.h"

//------------------------------------------
//set the sprite pos to her prev pos

void MovingObj::backToPrevPos()
{
	setPos(m_prevPos);
}
void MovingObj::beHurt()
{
	m_life -= LESS_LIFE;
}
//------------------------------------------
//return true if the sprite pos is out od the window
//else,return false

bool MovingObj::outWindow(sf::Vector2f pos, sf::Vector2f levelSize) const
{
	if (pos.x <= START_SPACE*1.5 || pos.y <= -10||
		//pos.y >= (levelSize.x * X_SPACE) - START_SPACE /3.1||
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


//--------------------------- collisionFromLeft --------------------------
// Returns if there was a collision from left side with a static object.
//------------------------------------------------------------------------
bool MovingObj::collisionFromLeft(GameObjBase& g) const
{
	return m_shape.getPosition().x <
		(g.getPos().x - g.getShape().getSize().x / 2);
}

//-------------------------- collisionFromRight ---------------------------
// Returns if there was a collision from right side with a static object.
//------------------------------------------------------------------------
bool MovingObj::collisionFromRight(GameObjBase& g) const
{
	return m_shape.getPosition().x >
		(g.getPos().x + g.getShape().getSize().x / 2);
}


//------------------------- collisionFromBelow ---------------------------
// Returns if there was a collision from below with a static object.
//------------------------------------------------------------------------
bool MovingObj::collisionFromBelow(GameObjBase& g) const
{
	return m_shape.getPosition().y < (g.getPos().y + g.getShape().getSize().y);
}
//----------------------- CollisionFromAboveFloor ------------------------
// Returns if there is collision from above with the floor.
//------------------------------------------------------------------------
bool MovingObj::CollisionFromAboveFloor(GameObjBase& floor) const
{
	/*return m_shape.getPosition().y + m_shape.getSize().x / 2.f <=
		(floor.getPos().y - floor.getShape().getSize().y / 2) &&
		m_shape.getPosition().x >=
		(floor.getPos().x - floor.getShape().getSize().x / 2) &&
		m_shape.getPosition().x <=
		(floor.getPos().x + floor.getShape().getSize().x / 2);*/

	if ((m_shape.getPosition().y + m_shape.getSize().y) >
		(floor.getPos().y + floor.getShape().getSize().y/2))
		return false;
	//if(m_left && (m_shape.getPosition().x < floor.getPos().x) ||
	//	(m_shape.getPosition().x > floor.getPos().x - floor.getShape().getSize().x))
	//	return false;
	//if((!m_left &&(m_shape.getPosition().x < floor.getPos().x) ||
	//		(m_shape.getPosition().x > floor.getPos().x + floor.getShape().getSize().x)))
	//{

	//	std::cout << "player pos y- " << m_shape.getPosition().y << "player size y- " << m_shape.getSize().y <<
	//		" floor pos y- " << floor.getPos().y << "Floor size y- " << floor.getShape().getSize().y << '\n';
	//	std::cout << "player pos x- " << m_shape.getPosition().x << "player size x- " << m_shape.getSize().x <<
	//		" floor pos x- " << floor.getPos().x << "Floor size x- " << floor.getShape().getSize().x << '\n';

	//	return false;
	//}
	//return true;

		/*if ((m_shape.getPosition().y + m_shape.getSize().y) >
		(floor.getPos().y + floor.getShape().getSize().y))
		return false;
	if(m_left && (m_shape.getPosition().x < floor.getPos().x) ||
		(m_shape.getPosition().x > floor.getPos().x - floor.getShape().getSize().x))
		return false;
	if((!m_left &&(m_shape.getPosition().x < floor.getPos().x) ||
			(m_shape.getPosition().x > floor.getPos().x + floor.getShape().getSize().x)))*/

	return true;
}
