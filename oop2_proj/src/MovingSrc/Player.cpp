#include "MovingInclude\Player.h"

//------------------------------- C-tor ----------------------------------
// Sets features using the base class constructor.
// Also, sets it's unique size and events clock.
//------------------------------------------------------------------------
Player::Player( const sf::Vector2f& pos)
	: MovingObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos),
	    m_animation(FileManager::p2FileManager().getPlayerData(),
		Operation::Stay, m_shape,
		FileManager::p2FileManager().getPlayerTexture())
{
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
void Player::move(sf::Vector2f levelSize)
{
	setPrevPos(m_shape.getPosition());
	if (isAlive())
	{
		
		auto movement = getMovement();
		m_shape.move(movement);
		setMovementStatus(movement);
		//handleEvents();//hendle collision
	}
	//else
	//{
	//	m_animation.operation(Operation::Dead);
	//}
	if (outWindow(m_shape.getPosition(), levelSize))
		this->backToPrevPos();

}

//
//------------------------- setMovementStatus ----------------------------
// Sets the movement status of the player and checks what is the new 
// movement the player preformed.
// Depending on the movement of the player, the function updates the
// data and presents the appropriate animation.
//------------------------------------------------------------------------
void Player::setMovementStatus(const sf::Vector2f& movement)
{
	//doorCollide = insideHurricane = onFloor = mvRight = mvLeft = false;

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


////-------------------------- setExtraJumpStatus --------------------------
//// Set the extra jump status.
//// We enter this function if the player collects the extra jump boost gem.
////------------------------------------------------------------------------
//void Player::setExtraJumpStatus()
//{
//	m_extraJumpBoost = JUMP_BOOST_BONUS;
//}
//
//
////------------------------------------------------------------------------
//// Checks if the player doesn't move. If he is not, plays the standing
//// animation.
////------------------------------------------------------------------------
//void Player::stayInPlaceAnimation(const sf::Vector2f& movement)
//{
//	if (movement == STAY_IN_PLACE &&
//		m_animation.getOperation() != Operation::Hit &&
//		m_animation.getOperation() != Operation::Shoot &&
//		m_animation.getOperation() != Operation::Hurt &&
//		!inHnaldeJump)
//	{
//		m_animation.operation(Operation::Stay);
//	}
//}
//
//
////------------------------------ moveShape -------------------------------
//// Moves the shape of the obejct and saves the old position for handle
//// collisions.
////------------------------------------------------------------------------
//void Player::moveShape(const sf::Vector2f& movement)
//{
//	//stayInPlaceAnimation(movement);
//	//m_oldPos = m_shape.getPosition();
//	m_shape.move(movement);
//}


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

//------------------------- isInsideHurricane ----------------------------
// Returns if the player is inside a hurricane.
// We want to want accurate behavior so we calculate by the position of 
// the player whether he is really inside the hurricane and not just 
// collided with him
////------------------------------------------------------------------------
//bool Player::isInsideHurricane(Hurricane& hurricane)
//{
//	return (m_shape.getPosition().x >= hurricane.getPosition().x
//		- hurricane.getShape().x / 2 &&
//		m_shape.getPosition().x <= hurricane.getPosition().x
//		+ hurricane.getShape().x / 2);
//}


//----------------------- playMovementAnimations -------------------------
 //Plays the animation according to the situation in which the player is.
//------------------------------------------------------------------------
void Player::playMovementAnimations()
{
	if (m_right || m_left)
	{
		//if (!inHnaldeJump)
		{
			if (m_animation.getOperation() != Operation::Hit )
				//&& m_animation.getOperation() != Operation::Hurt)
			{
				m_animation.operation(Operation::Walk);
			}
		}
		//else
		//{
		//	m_animation.operation(Operation::Jump);
		//}
		m_right = m_left = false;
	}
	/*else if (inHnaldeJump)
	{
		m_animation.operation(Operation::Jump);
	}*/
	else m_animation.operation(Operation::Stay);
}


////-------------------------- pushBackFromSpike ---------------------------
//// Pushes the player backwards depending on the location of his collision
//// with the spikes.
////------------------------------------------------------------------------
//void Player::pushBackFromSpike(Spike& spike)
//{
//	if (collisionFromLeft(spike) && m_shape.getPosition().y +
//		m_shape.getSize().y / 2 > spike.getPosition().y)
//	{
//		m_shape.move(-PUSH_FROM_SPIKE);
//	}
//	else if (collisionFromRight(spike) && m_shape.getPosition().y +
//		m_shape.getSize().y / 2 > spike.getPosition().y)
//	{
//		m_shape.move(PUSH_FROM_SPIKE);
//	}
//}


////---------------------------- getPosition -------------------------------
//// Returns the position of the player.
////------------------------------------------------------------------------
//const sf::Vector2f& Player::getPosition() const
//{
//	return m_shape.getPosition();
//}
//
//
////------------------------------ handleFall ------------------------------
//// Handle the fall of the player.
//// Assume that the player is falling.
//// Check what is the current position of the player.
//// If the current position of the player is not in 
//// the air ==> don't fall and exit.
//// If the player is falling ==> move the player downwards.
////------------------------------------------------------------------------
//void Player::handleFall()
//{
//	if (!inHnaldeJump && !onFloor && !insideHurricane)
//	{
//		inHandleFall = true;
//		falling = true;
//
//		move();
//
//		if (!onFloor)
//		{
//			m_animation.operation(Operation::Fall);
//		}
//
//		inHandleFall = false;
//	}
//}

//----------------------------- getMovement ------------------------------
// Returns the next move depending on the situation.
// i.e. if the player is falling, return a downward movement, if the is
// jumping, return a movement upwards + the wanted direction the user 
// wants. If the player is neither falling or jumping, return the next
// movement the user wants to preform.
////------------------------------------------------------------------------
const sf::Vector2f Player::getMovement()
{
	if (m_inHandleFall)
	{
		return FALL_PUSH;
	}
	else if (m_inHnaldeJump)
	{
		return ((getDirection() + UP_MOVEMENT) *m_deltaTime * HANDLE_JUMP_SPEED);
	}
	return getDirection() * m_deltaTime * (PLAYER_SPEED);
}


////------------------------- setExtraSpeedStatus --------------------------
//// Set the speed status of the player.
////------------------------------------------------------------------------
//void Player::setExtraSpeedStatus()
//{
//	m_extraSpeed = EXTRA_SPEED_BONUS;
//}


////-------------------------- turnOnDamageBoost ---------------------------
//// Turn on the damage bonus.
////------------------------------------------------------------------------
//void Player::turnOnDamageBoost()
//{
//	m_damageBoost = true;
//}


////----------------------------- pushFromBox ------------------------------
//// Pushses the player from the box.
////------------------------------------------------------------------------
//void Player::pushFromBox(Box& box, const sf::Vector2f& playerPush,
//	const sf::Vector2f& boxPush)
//{
//	if (box.isMoveAble())
//	{
//		box.move(boxPush);
//	}
//	else
//	{
//		m_shape.move(playerPush);
//	}
//}


////--------------------------- setPositionOnBox ---------------------------
//// Sets the position of the player when he is above the box so that he
//// will stand on it accurately.
////------------------------------------------------------------------------
//void Player::setPositionOnBox(Box& box)
//{
//	m_shape.setPosition(m_shape.getPosition().x,
//		box.getPosition().y - box.getShape().y / 2 - PUSH_FROM_BOX);
//	falling = false;
//	onFloor = true;
//}


////---------------------------- getExtraSpeed -----------------------------
//// Return the extra speed of the player.
//// If the player didn't collected the extra speed gem, the extra speed 
//// is by default zero.
////------------------------------------------------------------------------
//const bool Player::getExtraSpeed() const
//{
//	return m_extraSpeed;
//}


////---------------------------- getExtraJump ------------------------------
//// Return the extra jump bonus.
////------------------------------------------------------------------------
//const bool Player::getExtraJump() const
//{
//	return m_extraJumpBoost;
//}
//
//
////-------------------------- hasSpecialArrow -----------------------------
//// Return if the plyaer has a special arrow or not.
////------------------------------------------------------------------------
//const bool Player::hasSpecialArrow() const
//{
//	return m_damageBoost;
//}


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
void Player::handleJump(bool jump, sf::Vector2f levelSize)
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

	if (jumpCounter != 0)
	{
		jumpCounter--;
		move(levelSize);
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



//
////-------------------------- setHittingStatus ----------------------------
//// Sets the hitting status of the player.
////------------------------------------------------------------------------
//void Player::setHittingStatus(const bool status)
//{
//	m_hitingStatus = status;
//}







