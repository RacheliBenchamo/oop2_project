
#include "StaticInclude\Diamond.h"


Diamond::Diamond(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE/4, BLOCK_SIZE/6), pos),
	m_animation
	(FileManager::instance().getStaticData(DIAMOND),
		Stay,
		m_shape,
		FileManager::instance().getSharedStaticTexture(DIAMOND))
{
	m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getSize().y / 2);
	m_shape.setOrigin(m_shape.getOrigin().x, m_shape.getOrigin().y + m_shape.getSize().y / 2);
	m_shape.scale(1, 2.2f);
}
//--------------------------------------------------

void Diamond::startSound()
{
	
}