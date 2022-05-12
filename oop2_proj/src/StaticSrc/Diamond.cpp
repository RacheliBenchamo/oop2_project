
#include "StaticInclude\Diamond.h"


Diamond::Diamond(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos),
	m_animation
	(FileManager::p2FileManager().getStaticData(DIAMOND),
		Stay,
		m_shape,
		FileManager::p2FileManager().getSharedStaticTexture(DIAMOND))
{
	m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getSize().y / 2);
	m_shape.setOrigin(m_shape.getOrigin().x, m_shape.getOrigin().y + m_shape.getSize().y / 2);
	m_shape.scale(1, 2.2f);
}
//--------------------------------------------------

void Diamond::startSound()
{
	static sf::Sound effect;
	effect.setBuffer(*FileManager::p2FileManager().getSound(S_IN_TELEPORT));
	effect.play();
	effect.setVolume(VOLUME_COLLISION);
}