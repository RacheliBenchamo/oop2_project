#pragma once
#include "Gift.h"

class TakeToPrevLevelGift : public Gift
{
public:
	using Gift::Gift;
	~TakeToPrevLevelGift() {};

	virtual void handleCollision(King&) override { setDelete(); startSound();}
	virtual void handleCollision(Warrior&) override { setDelete(); startSound();}
	virtual void handleCollision(Mage&) override { setDelete(); startSound();}
	virtual void handleCollision(Thief&) override { setDelete(); startSound();}

};
