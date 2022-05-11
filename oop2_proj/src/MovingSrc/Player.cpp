#include "MovingInclude\Player.h"

//--------------------------------------------------
//handle player moving

void Player::move(sf::Time& deltaTime, sf::Vector2f levelSize)
{
	setCurrDir(getDirection());

	updateAnimation();

	sf::RectangleShape shape = getShape();
	setPrevPos(shape.getPosition());

	shape.move(getCurrDir() * BASE_SPEED * deltaTime.asSeconds());
	setShape(shape);

	//check bounds
	if (outWindow(shape.getPosition(),levelSize))
		this->backToPrevPos(); 
}


