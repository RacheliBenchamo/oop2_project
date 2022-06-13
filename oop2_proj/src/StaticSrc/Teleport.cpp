#include "StaticInclude\Teleport.h"

Teleport::Teleport(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE/1.2, BLOCK_SIZE/1.2), pos)
	{
	m_shape.setTexture(FileManager::instance().getSharedStaticTexture(TELEPORT));
	}
//--------------------------------------------------

void Teleport::setPartnerPos(sf::Vector2f pos)
{
    m_Partner = pos;
}
//--------------------------------------------------

void Teleport::toClose()
{
	m_isOpen = false;
}
//--------------------------------------------------

bool Teleport::isOpen()const
{
    return m_isOpen;
}

