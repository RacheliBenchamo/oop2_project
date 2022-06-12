#include "MovingInclude\\MovingObj.h"
#include "Macros.h"

//------------------------------------------
//set the sprite pos to her prev pos

MovingObj::MovingObj(const sf::Vector2f& pos, const sf::Vector2f& size,int level)
	:m_life(300),m_force(0),m_level(level),
	m_right(false),m_onFloor(false),
	m_inHnaldeJump(false),m_inHandleFall(false),
	m_hitingStatus(false),m_falling(false),
	m_up(false),m_down(false),GameObjBase(pos, size)
{
	setDamage();
}
//---------------------------------------------------

void MovingObj::setDamage()
{
	this->m_damage.setFont(*FileManager::instance().getFont());
	this->m_damage.setCharacterSize(STATUS_BAR_CHAR_SIZE - 1);
	this->m_damage.setFillColor(sf::Color::Red);
	this->m_damage.setOutlineThickness(0.5);
	this->m_damage.setOutlineColor(sf::Color::Red);
}
//---------------------------------------------------

void MovingObj::setDamagePos(const sf::Vector2f pos)
{
	m_damage.setPosition(pos.x, pos.y - 2);
}
//---------------------------------------------------

void MovingObj::printDamage(sf::RenderWindow& window)const
{
	window.draw(this->m_damage);
}
//---------------------------------------------------

void MovingObj::setDamageString(const int damage)
{
	this->m_damage.setString( " - " + std::to_string(damage));
}
//---------------------------------------------------

void MovingObj::backToPrevPos()
{
	setPos(m_prevPos);
}
//------------------------------------------
//return true if the sprite pos is out od the window
//else,return false

bool MovingObj::outWindow(const sf::Vector2f pos, const sf::Vector2f levelSize) const
{
	if (pos.x <= START_SPACE*2 || pos.y <= -10||
		pos.x >= (levelSize.y * Y_SPACE) + START_SPACE*2.8)
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
	return m_shape.getPosition().x >=
		(g.getPos().x );
}

//-------------------------- collisionFromRight ---------------------------
// Returns if there was a collision from right side with a static object.
//------------------------------------------------------------------------
bool MovingObj::collisionFromRight(GameObjBase& g) const
{
	return m_shape.getPosition().x <=(g.getPos().x);
}

//------------------------- collisionFromBelow ---------------------------
// Returns if there was a collision from below with a static object.
//------------------------------------------------------------------------

bool MovingObj::collisionFromBelow(GameObjBase& g) const
{
	return m_shape.getPosition().y >(g.getPos().y - g.getShape().getSize().y / 2);
}
//----------------------- CollisionFromAboveFloor ------------------------
// Returns if there is collision from above with the floor.
//------------------------------------------------------------------------
bool MovingObj::CollisionFromAboveFloor(GameObjBase& floor) const
{

	return m_shape.getPosition().y <=
		(floor.getPos().y - floor.getShape().getSize().y / 2);
	
}
//------------------------------------------------------------------------

bool MovingObj::CollisionFromAboveLeftFloor(GameObjBase& floor) const
{
	return m_shape.getPosition().x  >
		(floor.getPos().x + floor.getShape().getSize().x / 10);
}
//------------------------------------------------------------------------

bool MovingObj::CollisionFromAboveRightFloor(GameObjBase& floor) const
{
	return m_shape.getPosition().x < 
		(floor.getPos().x - floor.getShape().getSize().x / 10);
}
