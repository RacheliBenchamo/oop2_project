
#pragma once

#include "Board.h"
#include "StaticObj.h"
#include "Animation.h"



using std::vector;


class Floor :public StaticObj
{
public:
	//using StaticObj::StaticObj;
	Floor(sf::Vector2f ,int );
	virtual void startSound()override;



private:

};




