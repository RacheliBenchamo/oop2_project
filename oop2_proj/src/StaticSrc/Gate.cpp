#include "StaticInclude\Gate.h"

//--------------------------------------------------
//start touch gate sound

void Gate::startSound()
{
	static sf::Sound effect;
	effect.setBuffer(*FileManager::p2FileManager().getSound(S_TOUCH_GATE));
	effect.play();
	effect.setVolume(VOLUME_COLLISION);
}
//--------------------------------------------------

void Gate::handleCollision(GameObjBase& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
//--------------------------------------------------

void Gate::handleCollision(King& king)
{
	startSound();
	king.backToPrevPos();
}
//--------------------------------------------------

void Gate::handleCollision(Warrior& warr)
{
	startSound();
	warr.backToPrevPos();
}
//--------------------------------------------------

void Gate::handleCollision(Mage& mage)
{
	startSound();
	mage.backToPrevPos();
}
//--------------------------------------------------

void Gate::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}
//--------------------------------------------------

void Gate::handleCollision(Fairy& fairy)
{
	fairy.backAndChangeDir();
}
