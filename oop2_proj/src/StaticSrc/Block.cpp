#include "StaticInclude\Wall.h"

//--------------------------------------------------
//start touch wall sound

void Wall::startSound()
{
    static sf::Sound effect;
    effect.setBuffer(*FileManager::p2FileManager().getSound(S_TOUCH_WALL));
    effect.play();
    effect.setVolume(VOLUME_COLLISION);
}
//--------------------------------------------------

void Wall::handleCollision(GameObjBase& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//------------------------------------------

void Wall::handleCollision(King& king)
{
    startSound();
    king.backToPrevPos();
}
//------------------------------------------

void Wall::handleCollision(Warrior& warr)
{
    startSound();
    warr.backToPrevPos();
}
//------------------------------------------

void Wall::handleCollision(Mage& mage)
{
    startSound();
    mage.backToPrevPos();
}
//------------------------------------------

void Wall::handleCollision(Thief& thief)
{
    startSound();
    thief.backToPrevPos();
}
//------------------------------------------

void Wall::handleCollision(Fairy& fairy)
{
    fairy.backAndChangeDir();
}