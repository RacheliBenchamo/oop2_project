#include "MovingInclude\Monster.h"

//------------------------------- C-tor ----------------------------------
// Sets features using the base class constructor.
// Also, sets it's unique size and events clock.
//------------------------------------------------------------------------
Monster::Monster(const sf::Vector2f& pos, icons icon, 
	sf::Vector2f size, int force,int level)
	:MovingObj(size, pos + sf::Vector2f(0, 22), level),
	m_animation(FileManager::instance().getMonstersData(getCurrLevel(), icon),
		Operation::Stay, m_shape,
		FileManager::instance().getMonstersTexture(icon,getCurrLevel()))
	, m_monsterNum(icon)
{
	m_force = force;
	m_life = MAX_LIFE/3;
	m_shape.setSize({ m_shape.getSize() - sf::Vector2f{10, 10} });
	randDir();
}
//------------------------------------------------------------------------

void Monster::randDir()
{
	int dir = rand() % 2;

	switch ((direction)dir)
	{
	case RIGHT:
		m_lastDir = RIGHT_MOVEMENT;
		m_shape.setScale(SCALE_RIGHT);
		break;
	case LEFT:
		m_lastDir = LEFT_MOVEMENT;
		m_shape.setScale(SCALE_LEFT);
		break;
	}
}
//-------------------------------- move ----------------------------------
// Moves the enemy.
// The function works as follows:
// 1. checks if the movement is legal.
// 2. if the movement was legal, 
//------------------------------------------------------------------------
void Monster::move(const sf::Time& deltaTime, const sf::Vector2f levelSize)
{
	auto movement = getMove();

	m_shape.move(movement);

	if (outWindow(m_shape.getPosition(), levelSize)||!m_onFloor)
	{
		m_lastDir = -m_lastDir;
		m_shape.move(m_lastDir.x*2, 0);
		m_shape.setScale(-m_shape.getScale().x , 1);
	}
	m_onFloor = false;
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
			goAccordingToPlayerPos();
		}
		else
		{m_hitingStatus = false;}
	}
}

//------------------------------ handleHit -------------------------------
// Handles the player hit.
// Absorbs the blow of the player.
// Uses polymorphic functions activates the appropriate animations and
// sounds.
//------------------------------------------------------------------------
void Monster::handleHit(const float_t damage)
{
	static bool dead = false;

		if (isAlive())
		{
			m_life - PLAYER_DAMAGE <= 0 ? m_life = 0 : m_life -= PLAYER_DAMAGE;
			m_animation.operation(Operation::Hurt);
			goAccordingToPlayerPos();
			pushFrom();
			setDamagePos(m_shape.getPosition() - m_shape.getSize());
			setDamageString(damage);
			setHurt(true);

		}
		else
		{
			if (!dead)
			{
				m_animation.operation(Operation::Dead);
				dead = true;
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				setToDelete();
			}
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

	if (m_animation.getOperation() == Operation::Hurt ||
		m_animation.getOperation() == Operation::Hit)
	{
		return STAY_IN_PLACE;
	}
	if (movementClock.getElapsedTime().asSeconds() <= 2)
	{
		m_animation.operation(Operation::Walk);
		return m_lastDir;
	}
	else if (movementClock.getElapsedTime().asSeconds() <= 4)
	{
		m_animation.operation(Operation::Stay);
		return STAY_IN_PLACE;
	}
	else if (movementClock.getElapsedTime().asSeconds() <= 6)
	{
		m_animation.operation(Operation::Walk);
		return m_lastDir;
	}
	else if (movementClock.getElapsedTime().asSeconds() >= 6 &&
		movementClock.getElapsedTime().asSeconds() <= 8)
	{
		m_animation.operation(Operation::Stay);
		return STAY_IN_PLACE;
	}

	movementClock.restart();
	return m_lastDir;
}
//-------------------------- handleCollision -----------------------------
// Handles collision with the floor.
// Pushes the moving object off the floor depending on the location of the
// collision.
//------------------------------------------------------------------------
void Monster::handleCollisionFloor(const GameObjBase& floor)
{
	if (CollisionFromAboveFloor(floor))
	{
		m_falling = false;
		m_onFloor = true;
	}
}
//------------------------------------------------------------------------
void Monster::goAccordingToPlayerPos()
{
	if (m_shape.getPosition().x < m_playerPos.x)
	{
		m_lastDir = RIGHT_MOVEMENT;
		m_shape.setScale(SCALE_RIGHT);
	}
	else
	{
		m_lastDir = LEFT_MOVEMENT;
		m_shape.setScale(SCALE_LEFT);
	}
}

//-----------------------------------

void Monster::pushFrom()
{
	if (m_playerPos.x >= m_shape.getPosition().x)
		m_shape.move(-PUSH_FROM_MONSTER);
	else
		m_shape.move(PUSH_FROM_MONSTER);
}