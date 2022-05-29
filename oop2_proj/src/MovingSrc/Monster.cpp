#include "MovingInclude\Monster.h"

//------------------------------- C-tor ----------------------------------
// Sets features using the base class constructor.
// Also, sets it's unique size and events clock.
//------------------------------------------------------------------------
Monster::Monster(const sf::Vector2f& pos, levels lev, icons icon, sf::Vector2f size)
	:MovingObj(size, pos),
	m_animation(FileManager::p2FileManager().getMonstersData(lev, icon),
		Operation::Stay, m_shape,
		FileManager::p2FileManager().getMonstersTexture(icon,lev))
{
	m_shape.setSize({ m_shape.getSize() - sf::Vector2f{10, 10} });
}

//-------------------------------- move ----------------------------------
// Moves the enemy.
// The function works as follows:
// 1. checks if the movement is legal.
// 2. if the movement was legal, 
//------------------------------------------------------------------------
void Monster::move(sf::Time& deltaTime, sf::Vector2f levelSize)
{
	m_onFloor = false;

	setPrevPos(m_shape.getPosition());
	auto movement = getMove();

	m_shape.move(movement);

	//MoveObject::handleEvents();

	if (outWindow(m_shape.getPosition(), levelSize))
		this->backToPrevPos();
}

//---------------------------- isPlayerClose -----------------------------
// Returns if the player is close.
//------------------------------------------------------------------------
bool Monster::isPlayerClose()
{
	return (std::abs(m_shape.getPosition().x -	m_playerPos.x) < m_shape.getSize().x * 5);
}
//--------------------------------- hit ----------------------------------
// Performs a hit operation.
// We will reach this function only if the player the enemy have collided.
// The function recives the enemy with which the collision was and
// activates polymorphic functions that are unique to the specific type
// of enemy.
//------------------------------------------------------------------------
void Monster::hit()
{
	if (isAlive())
	{
		if (m_animation.getOperation() != Operation::Hurt)
		{
			m_hitingStatus = true;
			//playAttackSound();
			scaleAccordingToPlayerPos();
			//m_animation.operation(Operation::Hit);
		}
		else
		{
			m_hitingStatus = false;
		}
	}
}

//------------------------------ handleHit -------------------------------
// Handles the player hit.
// Absorbs the blow of the player.
// Uses polymorphic functions activates the appropriate animations and
// sounds.
//------------------------------------------------------------------------
void Monster::handleHit()
{
	if (isAlive())
	{
		m_life-=PLAYER_DAMAGE;
		if (isAlive())
		{
			//m_animation.operation(Operation::Hurt);
			//e.playHurtSound();
		}
		else
		{
			//e.playDeathSound();
		}
	}
	else
	{
		//m_animation.operation(Operation::Dead);
	}
}



//------------------------------- getMove --------------------------------
// Return the next move of the Bear.
// The next move is selected by the time passed. 
// The Constant Enemy changes it's scale every X seconds.
//------------------------------------------------------------------------
sf::Vector2f Monster::getMove()
{
	// static timer to have the movement every X time
	static sf::Clock movementClock;

	//if (m_animation.getOperation() == Operation::Hurt ||
	//	m_animation.getOperation() == Operation::Hit)
	//{
	//	return STAY_IN_PLACE;
	//}

	//if (movementClock.getElapsedTime().asSeconds() <= 2)
	//{
	//	m_animation.operation(Operation::Walk);
	//	m_shape.setScale(SCALE_LEFT);
	//	return LEFT_MOVEMENT;
	//}
	//else if (movementClock.getElapsedTime().asSeconds() <= 4)
	//{
	//	m_animation.operation(Operation::Stay);
	//	return STAY_IN_PLACE;
	//}
	//else if (movementClock.getElapsedTime().asSeconds() <= 6)
	//{
	//	m_animation.operation(Operation::Walk);
	//	m_shape.setScale(SCALE_RIGHT);
	//	return RIGHT_MOVEMENT;
	//}
	//else if (movementClock.getElapsedTime().asSeconds() >= 6 &&
	//	movementClock.getElapsedTime().asSeconds() <= 8)
	//{
	//	m_animation.operation(Operation::Stay);
	//	return STAY_IN_PLACE;
	//}

	//movementClock.restart();
	//m_animation.operation(Operation::Stay);
	//m_shape.setScale(SCALE_LEFT);
	//return LEFT_MOVEMENT;

	return{ 0,0 };

}

////---------------------------- setEventsClock ----------------------------
//// Sets the events clock of the current enemy.
////------------------------------------------------------------------------
//void Enemy::setEventsClock()
//{
//	MoveObject::setEventsClock(ENEMY_HIT_RATIO);
//}


//---------------------------- setOperation ------------------------------
// sets the operation of the animation.
//------------------------------------------------------------------------
void Monster::setOperation(const Operation op)
{
	m_animation.operation(op);
}


//----------------------- scaleAccordingToPlayerPos ----------------------
// Scales the enemy according to the player position.
//------------------------------------------------------------------------
void Monster::scaleAccordingToPlayerPos()
{
	if (m_shape.getPosition().x < m_playerPos.x)
	{
		m_shape.setScale(SCALE_RIGHT);
	}
	else
	{
		m_shape.setScale(SCALE_LEFT);
	}
}

//-------------------------- handleCollision -----------------------------
// Handles collision with the floor.
// Pushes the moving object off the floor depending on the location of the
// collision.
//------------------------------------------------------------------------
void Monster::handleCollision(GameObjBase& floor)
{
	if (!CollisionFromAboveFloor(floor))
	{
		setPrevPos(m_shape.getPosition());
		m_falling = false;
		m_onFloor = true;
		//getNewDir();
	}
}