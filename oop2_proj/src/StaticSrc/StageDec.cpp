#include "StaticInclude\StageDec.h"


StageDec::StageDec(sf::Vector2f pos, levels level_num, decoration dec)
	: StaticObj(sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE * 2), pos)
{
	auto m_pTexture = FileManager::p2FileManager().getDec();
	m_shape.setTexture(m_pTexture);
	m_rect = FileManager::p2FileManager().getCurrLevDecRect(level_num, dec);

	m_shape.setTextureRect(m_rect);
	//m_shape.setSmooth(true);
}

//--------------------------------------------------

//void StageDec::startSound()
//{
//	static sf::Sound effect;
//	effect.setBuffer(*FileManager::p2FileManager().getSound(S_IN_TELEPORT));
//	effect.play();
//	effect.setVolume(VOLUME_COLLISION);
//}
////--------------------------------------------------
//
//void StageDec::handleCollision(GameObjBase& gameObject)
//{
//	if (&gameObject == this) return;
//	// double dispatch
//	gameObject.handleCollision(*this);
//}
