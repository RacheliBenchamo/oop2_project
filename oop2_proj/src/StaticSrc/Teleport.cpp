#include "StaticInclude\Teleport.h"

Teleport::Teleport(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), pos),
		m_animation
		(   FileManager::instance().getStaticData(TELEPORT),
			Stay,
			m_shape,
			FileManager::instance().getSharedStaticTexture(TELEPORT))
	{
		m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getSize().y / 2);
		m_shape.setOrigin(m_shape.getOrigin().x, m_shape.getOrigin().y + m_shape.getSize().y / 2);
		m_shape.scale(1, 2.2f);
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
//--------------------------------------------------

bool Teleport::isOpen()
{
    return m_isOpen;
}

