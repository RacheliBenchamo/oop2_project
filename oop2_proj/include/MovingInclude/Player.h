#pragma once
#include "MovingInclude\MovingObj.h"



class Player :public MovingObj
{
public:
	using MovingObj::MovingObj;
	virtual void move(sf::Time&, sf::Vector2f)override;

private:

};

