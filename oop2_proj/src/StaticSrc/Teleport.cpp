#include "StaticInclude\Teleport.h"

Teleport::Teleport(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE/1.2, BLOCK_SIZE/1.2), pos)
	{
	m_shape.setTexture(FileManager::instance().getSharedStaticTexture(TELEPORT));
		/*m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getSize().y / 2);
		m_shape.setOrigin(m_shape.getOrigin().x, m_shape.getOrigin().y + m_shape.getSize().y / 2);
		m_shape.scale(1, 2.2f);*/
	}

//--------------------------------------------------

void Teleport::startSound()
{

}
//--------------------------------------------------

void Teleport::setPartnerPos(sf::Vector2f pos)
{
    m_Partner = pos;
}
void Teleport::toClose()
{
	m_isOpen = false;
	static sf::Sound effect;
	effect.setBuffer(*FileManager::instance().getShareSaund(S_IN_TELEPORT));
	effect.play();
	effect.setVolume(VOLUME_COLLISION);

}
//--------------------------------------------------

bool Teleport::isOpen()
{
    return m_isOpen;
}

