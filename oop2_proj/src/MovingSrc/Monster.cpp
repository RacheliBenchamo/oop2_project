#include "MovingInclude\Monster.h"


Monster::Monster(const sf::Vector2f& pos, objects icon,
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
//------------------------------------------
//rand starting direction for each monster

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
//------------------------------------------
// Moves the monster

void Monster::move(const sf::Time& deltaTime,
	const sf::Vector2f levelSize)
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
//------------------------------------------
// Returns if the player is close.
//base for smart monsters

bool Monster::isPlayerClose()
{
	return (std::abs(m_shape.getPosition().x -	
		m_playerPos.x) < m_shape.getSize().x * 5);
}
//------------------------------------------
// Performs a hit operation.
// We will reach this function only if the
// player the monster have collided.The function
// recives the monster with which the collision 
// was and activates polymorphic functions that
// are unique to the specific type of monster.

void Monster::hit()
{
	if (isAlive())
	{
		if (m_animation.getOperation() != Hurt)
		{
			m_hitingStatus = true;
			goAccordingToPlayerPos();
		}
		else
		{m_hitingStatus = false;}
	}
}

//------------------------------------------
// Handles the player hit.
// Absorbs the blow of the player.
// Uses polymorphic functions activates 
//the appropriate animations.

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
//------------------------------------------
// Return the next move of the monster.
// The next move is selected by the time passed. 
// The Constant Enemy changes it's scale every 
//X seconds.

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
//------------------------------------------
// Handles collision with the floor.

void Monster::handleCollisionFloor(const GameObjBase& floor)
{
	if (CollisionFromAboveFloor(floor))
			m_onFloor = true;
}
//------------------------------------------
//change direction according to player position

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
//------------------------------------------
//when the player hit the monster she pushed 
//from him

void Monster::pushFrom()
{
	if (m_playerPos.x >= m_shape.getPosition().x)
		m_shape.move(-PUSH_FROM_MONSTER);
	else
		m_shape.move(PUSH_FROM_MONSTER);
}