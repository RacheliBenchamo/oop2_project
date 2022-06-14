#include "StaticInclude\StageDec.h"

StageDec::StageDec(sf::Vector2f pos, levels level_num, 
	decoration dec, sf::Vector2f size,
	const int place)
	: StaticObj(size, pos)
{
	auto m_pTexture = FileManager::instance().getDec(place);
	m_shape.setTexture(m_pTexture);
	m_shape.setTextureRect(FileManager::instance()
		.getCurrLevDecRect(level_num, dec));
}
