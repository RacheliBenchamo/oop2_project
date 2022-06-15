#include "MovingInclude\Player.h"


Player::Player( const sf::Vector2f& pos, gender gen,const int level)
	: MovingObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos,level),
	    m_animation(FileManager::instance().getPlayerData(gen),
		Operation::Stay, m_shape,
		FileManager::instance().getPlayerTexture()),
		m_diamondsCount(0)
{
	m_force = PAYER_FORCE;
	m_life = MAX_LIFE;
	m_power = MAX_POWER;
	m_shape.setSize({ m_shape.getSize() - sf::Vector2f{10, 10} });
}
//------------------------------------------
// Moves the player according to the players request.
// The player moves only if he is alive.
// the function works as follows:
// 1. Gets the next requested action(movement).
// 2. sets all the movement stats back to false.
// 3. Moves the shape of the player.
// 4. Handles all the possible events that can accure in the game.

void Player::move(const sf::Time& deltaTime, const sf::Vector2f levelSize)
{
	setPrevPos(m_shape.getPosition());
	if (isAlive())
	{
		auto movement = getMovement(deltaTime);
		m_shape.move(movement);
		setMovementStatus(movement);
		stayInPlaceAnimation(movement);
	}
	if (outWindow(m_shape.getPosition(), levelSize))
		this->backToPrevPos();
}
//------------------------------------------
//Sets the movement status of the player and 
// checks what is the new 
// movement the player preformed.
// Depending on the movement of the player,
// the function updates the
// data and presents the appropriate animation.

void Player::setMovementStatus(const sf::Vector2f& movement)
{
	m_climbing=m_onFloor=m_right = m_left = false;

	if (movement.x < 0)
	{
		m_shape.setScale(SCALE_LEFT);
		m_left = true;
	}
	if (movement.x > 0)
	{
		m_shape.setScale(SCALE_RIGHT);
		m_right = true;
	}
	playMovementAnimations();
}
//------------------------------------------
// Checks if the player doesn't move. 
// If he is not, plays the standing animation.

void Player::stayInPlaceAnimation(const sf::Vector2f& movement)
{
	if (movement == STAY_IN_PLACE &&
		m_animation.getOperation() != Hit &&
		m_animation.getOperation() != Hurt &&
		!m_inHnaldeJump)
	{
		m_animation.operation(Stay);
	}
}
//------------------------------------------
//Plays the animation according to the
//situation in which the player is.

void Player::playMovementAnimations()
{
	if (m_right || m_left)
	{
		if (!m_inHnaldeJump)
		{
			if (m_animation.getOperation() != Operation::Hit 
				&& m_animation.getOperation() != Operation::Hurt)
			{
				FileManager::instance().startSound(FileManager::instance()
					.getPlayerSound(WALK,getCurrLevel()), VOLUME_BG);
				m_animation.operation(Operation::Walk);
			}
		}
		else
          m_animation.operation(Operation::Jump);
		
		m_right = m_left = false;
	}
	else if (m_inHnaldeJump)
	{
		m_animation.operation(Operation::Jump);
	}
}
//------------------------------------------
//Handle the fall of the player.
//Assume that the player is falling.
//Check what is the current position of the player.
//If the current position of the player is not in 
//the air => don't fall and exit.
//If the player is falling => move the player downwards.

void Player::handleFall(const sf::Time& deltaTime, const sf::Vector2f levelSize)
{
	if (!m_inHnaldeJump && !m_onFloor && !m_climbing)
	{
		m_inHandleFall = true;
		m_falling = true;
		move(deltaTime,levelSize);

		if (!m_onFloor)
			m_animation.operation(Operation::Jump);
		m_inHandleFall = false;
	}
}
//------------------------------------------
// Returns the next move depending on the situation.
// i.e. if the player is falling, return a downward movement, if the is
// jumping, return a movement upwards + the wanted direction the user 
// wants.if the player climbing check if hr press up or down
// If the player is neither falling, climbing or jumping, return the next
// movement the user wants to preform.

const sf::Vector2f Player::getMovement(const sf::Time& deltaTime)
{
	if (m_inHandleFall)
	{
		return FALL_PUSH;
	}
	else if (m_climbing)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			return UP_MOVEMENT;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			return DOWN_MOVEMENT;
		return STAY_IN_PLACE;
	}
	else if (m_inHnaldeJump)
	{
	/*	FileManager::instance().startSound(FileManager::instance()
			.getPlayerSound(JUMP,getCurrLevel()), VOLUME_BG);*/
		return ((getDirection() + UP_MOVEMENT) * 
			deltaTime.asSeconds() * HANDLE_JUMP_SPEED);
	}
	return (getDirection() * deltaTime.asSeconds() * (PLAYER_SPEED));
}
//------------------------------------------
//Prints the player upon the window.

void Player::draw(sf::RenderWindow& window)
{
	auto temp_shape = m_shape;

	switch (m_animation.getOperation())
	{
	case Stay:
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;

	case Walk:
		temp_shape.scale(WALK_SCALE);
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;
	case Fall:
	case Jump:
		temp_shape.scale(JUMP_SCALE);
		break;
	case Hit:
		temp_shape.scale(HIT_SCALE);
		break;
	}
	window.draw(temp_shape);
}
//------------------------------------------
// The player reguests to attack.Therefore, 
// we needed to update the
//status of the hit and display the hiting animation.

void Player::hit()
{
	if (m_power > 0 && m_onFloor )
	{
		m_power - HITTING_POWER<=0? m_power=0: m_power -= HITTING_POWER;
		m_hitingStatus = true;
		m_animation.operation(Hit);
	}
}
//------------------------------------------
// handles the jump event.
// The player is shifted upwards with calling the function move that knows
// how to handle the various events that can happen during the jump and
// act accordingly.

void Player::handleJump(const sf::Time& deltaTime, const bool jump,
	const sf::Vector2f levelSize)
{
	static int jumpCounter = 0;

	m_inHnaldeJump = true;
	if (jump && m_onFloor && jumpCounter == 0&& !m_climbing)
	{
		m_falling = true;
		m_onFloor = false;
		jumpCounter = JUMP_COUNTER;
	}
	else if (jumpCounter != 0)
	{
		jumpCounter--;
		move(deltaTime,levelSize);
	}
	else
	{
		m_inHnaldeJump = false;
		jumpCounter = 0;
	}
}
//------------------------------------------
// Sets the hitting status of the player.

void Player::setHittingStatus(const bool status)
{
	m_hitingStatus = status;
}
//------------------------------------------
//add diamond

void Player::addDiamond()
{
	m_diamondsCount++; 

	if (m_diamondsCount == m_maxDiamond)
	{
		static sf::Sound effect;
		if (FileManager::instance().getToPlayAudio())
		{
			effect.setBuffer(*FileManager::instance().getShareSaund(S_REACHED_ALL_DIAMONDS));
			effect.setVolume(VOLUME_COLLISION);
			effect.play();
		}
	}
}
//------------------------------------------
// handles the hiting by monsters event.

void Player::handleHit(const float_t damage)
{
	static int hitCounter = 0;
	if (hitCounter == 0)
	{
		hitCounter = HIT_COUNTER;
		m_life - damage <= 0 ? m_life = 0 : m_life -= damage;
	}
	else if (hitCounter >= 1)
	{
		m_animation.operation(Operation::Hurt);
		hitCounter--;
		setDamagePos(m_shape.getPosition() - m_shape.getSize());
		setDamageString(damage);
		setHurt(true);
	}
	else
		hitCounter = 0;
}
//------------------------------------------
// handles the climbing event.

void Player::handleClimbing()
{
	if (m_climbing)
		m_animation.operation(Operation::Climbe);
}

//------------------------------------------
// Handles collision with the floor.
// Pushes the moving object off the floor depending 
// on the location of the collision.

void Player::handleCollisionFloor(const GameObjBase& floor)
{
	 if (CollisionFromAboveFloor(floor))
	{
		m_falling = false;
		m_onFloor = true;
	}
	 else if (collisionFromBelow(floor))
		 m_shape.move(FALL_PUSH);
}
//------------------------------------------
// Handles collision with the left edge of the floor.
// Pushes the moving object off the floor depending 
// on the location of the collision.

void Player::handleCollisionLeftFloor(const GameObjBase& floor)
{
	if (CollisionFromAboveFloor(floor) &&(
		CollisionFromAboveLeftFloor(floor) ||
		m_shape.getScale() != SCALE_LEFT))
	{
		m_falling = false;
		m_onFloor = true;
	}
	else if (collisionFromBelow(floor))
		m_shape.move(FALL_PUSH);
	else if (collisionFromLeft(floor))
	{
		m_shape.move(-PUSH_FROM);
	}
}
//------------------------------------------
// Handles collision with the right edge of the floor.
// Pushes the moving object off the floor depending 
// on the location of the collision.

void Player::handleCollisionRightFloor(const GameObjBase& floor)
{
	 if (CollisionFromAboveFloor(floor)&&(
		 CollisionFromAboveRightFloor(floor)||
		 m_shape.getScale()!= SCALE_RIGHT))
	{

		m_falling = false;
		m_onFloor = true;
	}
	else if (collisionFromBelow(floor) )
		 m_shape.move(FALL_PUSH);
	else if (collisionFromRight(floor))
	{
	m_shape.move(PUSH_FROM);
	}
}