#include "MovingInclude\Player.h"

//--------------------------------------------------
//handle player moving

void Player::move(sf::Time& deltaTime, sf::Vector2f levelSize)
{
	setCurrDir(getDirection());

	updateAnimation();

	sf::Sprite sprite = getSprite();
	setPrevPos(sprite.getPosition());

	sprite.move(getCurrDir() * BASE_SPEED * deltaTime.asSeconds());
	setSprite(sprite);

	//check bounds
	if (outWindow(sprite.getPosition(),levelSize))
		this->backToPrevPos(); 
}


