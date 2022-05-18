#include "StaticInclude\Floor.h"


Floor::Floor(sf::Vector2f pos,int level_num)
	: StaticObj(sf::Vector2f(BLOCK_SIZE*2, BLOCK_SIZE*2), pos)
{
//auto m_pTexture = FileManager::p2FileManager().getCurrLevDec(FLOOR,level_num);
//m_shape.setTexture(m_pTexture);
}

//--------------------------------------------------

void Floor::startSound()
{
	static sf::Sound effect;
	effect.setBuffer(*FileManager::p2FileManager().getSound(S_IN_TELEPORT));
	effect.play();
	effect.setVolume(VOLUME_COLLISION);
}
//--------------------------------------------------

void Floor::handleCollision(GameObjBase& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
