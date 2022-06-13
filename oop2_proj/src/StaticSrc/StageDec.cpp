#include "StaticInclude\StageDec.h"


StageDec::StageDec(sf::Vector2f pos, levels level_num, decoration dec, sf::Vector2f size,
	const int place)
	: StaticObj(size, pos)
{
	auto m_pTexture = FileManager::instance().getDec(place);
	m_shape.setTexture(m_pTexture);
	m_shape.setTextureRect(FileManager::instance().getCurrLevDecRect(level_num, dec));
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
