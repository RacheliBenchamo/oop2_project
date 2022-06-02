#include "MovingInclude\Player.h"

//------------------------------- C-tor ----------------------------------
// Sets features using the base class constructor.
// Also, sets it's unique size and events clock.
//------------------------------------------------------------------------
Player::Player( const sf::Vector2f& pos)
	: MovingObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos),
	    m_animation(FileManager::instance().getPlayerData(),
		Operation::Stay, m_shape,
		FileManager::instance().getPlayerTexture())
{
	m_force = PAYER_FORCE;
	m_life = 1000;
	m_power = 1000;
	m_shape.setSize({ m_shape.getSize() - sf::Vector2f{10, 10} });
}


//------------------------------- move -----------------------------------
// Moves the player according to the players request.
// The player moves only if he is alive. Otherwise, the death animation
// is played.
// 
// the function works as follows:
// 1. Gets the next requested action(movement).
// 2. sets all the movement stats back to false.
// 3. Moves the shape of the player.
// 4. Handles all the possible events that can accure in the game.
//------------------------------------------------------------------------
void Player::move(sf::Time& deltaTime,sf::Vector2f levelSize)
{
	setPrevPos(m_shape.getPosition());
	if (isAlive())
	{
		auto movement = getMovement(deltaTime);
		m_shape.move(movement);
		setMovementStatus(movement);
		stayInPlaceAnimation(movement);

		//handleEvents();//hendle collision
	}
	//else
	//{
	//	m_animation.operation(Operation::Dead);
	//}

	if (outWindow(m_shape.getPosition(), levelSize))
		this->backToPrevPos();
}

//------------------------- setMovementStatus ----------------------------
// Sets the movement status of the player and checks what is the new 
// movement the player preformed.
// Depending on the movement of the player, the function updates the
// data and presents the appropriate animation.
//------------------------------------------------------------------------
void Player::setMovementStatus(const sf::Vector2f& movement)
{
	m_onFloor=m_right = m_left = false;

	if (movement.x < 0)
	{
		setScale(SCALE_LEFT);
		m_left = true;
	}
	if (movement.x > 0)
	{
		setScale(SCALE_RIGHT);
		m_right = true;
	}

	playMovementAnimations();
}

////------------------------------------------------------------------------
//// Checks if the player doesn't move. If he is not, plays the standing
//// animation.
////------------------------------------------------------------------------
void Player::stayInPlaceAnimation(const sf::Vector2f& movement)
{
	if (movement == STAY_IN_PLACE &&
		m_animation.getOperation() != Operation::Hit &&
		//m_animation.getOperation() != Operation::Hurt &&
		!m_inHnaldeJump)
	{
		m_animation.operation(Operation::Stay);
	}
}
//---------------------------- setEventsClock ----------------------------
// Set the extra jump status.
// We enter this function if the player collects the extra jump boost gem.
////------------------------------------------------------------------------
//void Player::setEventsClock()
//{
//	MoveObject::setEventsClock(FIST_RATIO);
//	MoveObject::setEventsClock(SHOOT_RATIO);
//}
//

//----------------------- playMovementAnimations -------------------------
 //Plays the animation according to the situation in which the player is.
//------------------------------------------------------------------------
void Player::playMovementAnimations()
{
	if (m_right || m_left)
	{
		if (!m_inHnaldeJump)
		{
			if (m_animation.getOperation() != Operation::Hit )
				//&& m_animation.getOperation() != Operation::Hurt)
			{
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

////------------------------------ handleFall ------------------------------
//// Handle the fall of the player.
//// Assume that the player is falling.
//// Check what is the current position of the player.
//// If the current position of the player is not in 
//// the air ==> don't fall and exit.
//// If the player is falling ==> move the player downwards.
////------------------------------------------------------------------------
void Player::handleFall( sf::Time& deltaTime, sf::Vector2f levelSize)
{
	if (!m_inHnaldeJump && !m_onFloor)
	{
		m_inHandleFall = true;
		m_falling = true;

		move(deltaTime,levelSize);

		if (!m_onFloor)
			m_animation.operation(Operation::Stay);

		m_inHandleFall = false;
	}
}

//----------------------------- getMovement ------------------------------
// Returns the next move depending on the situation.
// i.e. if the player is falling, return a downward movement, if the is
// jumping, return a movement upwards + the wanted direction the user 
// wants. If the player is neither falling or jumping, return the next
// movement the user wants to preform.
////------------------------------------------------------------------------
const sf::Vector2f Player::getMovement(sf::Time& deltaTime)
{
	if (m_inHandleFall)
	{
		return FALL_PUSH;
	}
	else if (m_inHnaldeJump)
	{
		return ((getDirection() + UP_MOVEMENT) * deltaTime.asSeconds() * HANDLE_JUMP_SPEED);
	}

	return (getDirection() * deltaTime.asSeconds() * (PLAYER_SPEED));
}

////------------------------------- draw -----------------------------------
//// Prints the player upon the window.
////------------------------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
	auto temp_shape = m_shape;

	switch (m_animation.getOperation())
	{
	case Operation::Stay:
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;

	case Operation::Walk:
		temp_shape.scale(WALK_SCALE);
		temp_shape.setPosition(temp_shape.getPosition().x,
			temp_shape.getPosition().y +
			temp_shape.getOrigin().y / HALF_SIZE);
		break;

	case Operation::Fall:
	case Operation::Jump:
		temp_shape.scale(JUMP_SCALE);
		break;
	case Operation::Hit:
		temp_shape.scale(HIT_SCALE);
		break;
	}
	window.draw(temp_shape);
}

////-------------------------------- hit -----------------------------------
//// The player reguests to attack. Therefore, we needed to update the
//// status of the hit and display the hiting animation.
////------------------------------------------------------------------------
void Player::hit()
{
	//&& isEventDelayPassed(FIST_ATTACK)
	if (m_power > 0 && m_onFloor )
	{
		//Resources::instance().playSound(PLAYER_ATTACK_SOUND);
		m_power - HITTING_POWER<=0? m_power=0: m_power -= HITTING_POWER;
		m_hitingStatus = true;
		m_animation.operation(Operation::Hit);
	}
}
////----------------------------- handleJump -------------------------------
//// handles the jump event.
//// The player is shifted upwards with calling the function move that knows
//// how to handle the various events that can happen during the jump and
//// act accordingly.
//// If the player has collected the jump bonus, the loop that calls the 
//// move function will be summoned more times to elevate the player
//// further upwards.
////------------------------------------------------------------------------
void Player::handleJump(sf::Time& deltaTime,bool jump, sf::Vector2f levelSize)
{

	static int jumpCounter = 0;

	m_inHnaldeJump = true;
	if (jump && m_onFloor && jumpCounter == 0)
	{
		//Resources::instance().playSound(JUMP_SOUND);
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

////------------------------------- shoot ----------------------------------
//// Plays the shoot animation.
////------------------------------------------------------------------------
//void Player::hit()
//{
//	m_animation.operation(Operation::Hit);
//}

////-------------------------- setHittingStatus ----------------------------
//// Sets the hitting status of the player.
////------------------------------------------------------------------------
void Player::setHittingStatus(const bool status)
{
	m_hitingStatus = status;
}
//---------------------------------------------------------

void Player::handelHit(int force)
{
	static int hitCounter = 0;

	if (hitCounter == 0)
	{
		hitCounter = HIT_COUNTER;
		// play sound
		m_life - force <= 0 ? m_life = 0 : m_life -= force;
	}
	else if (hitCounter != 0)
	{
		m_animation.operation(Operation::Hurt);
		hitCounter--;
	}
	else
		hitCounter = 0;
}

//-------------------------- handleCollision -----------------------------
// Handles collision with the floor.
// Pushes the moving object off the floor depending on the location of the
// collision.
//------------------------------------------------------------------------
void Player::handleCollisionFloor(GameObjBase& floor)
{


	     if (CollisionFromAboveFloor(floor))
	{

		m_falling = false;
		m_onFloor = true;
	}
	// else if (collisionFromRight(floor))
	// {
	//	 std::cout << "r\n";
	//	 backToPrevPos();
	////	 m_shape.move(PUSH_FROM);
	// }

	//  else if (collisionFromLeft(floor))
	// {
	//	 std::cout << "l\n";
	//	 backToPrevPos();

	//	// m_shape.move(-PUSH_FROM);
	// }
	 if (collisionFromBelow(floor))
		 m_shape.move(FALL_PUSH);



}
//------------------------------------------------------------------------
void Player::handleCollisionLeftFloor(GameObjBase& floor)
{
	std::cout << "l\n";


	if (collisionFromLeft(floor))
	{
		backToPrevPos();
	m_shape.move(-PUSH_FROM); 
	}
	else if (collisionFromLeft(floor))
	{
		backToPrevPos();

		// m_shape.move(-PUSH_FROM);
	}
	
}
//------------------------------------------------------------------------
void Player::handleCollisionRightFloor(GameObjBase& floor)
{
	std::cout << "right "<< "player: " << m_shape.getPosition().x << " floor: " << floor.getPos().x << "\n";
	if (collisionFromBelow(floor))
		m_shape.move(FALL_PUSH);
	else if (CollisionFromAboveFloor(floor)&&CollisionFromAboveRightFloor(floor))
	{

		m_falling = false;
		m_onFloor = true;
	}
	else if (collisionFromRight(floor))
	{
		std::cout << "from right\n";
	m_shape.move(PUSH_FROM);
	}

}





