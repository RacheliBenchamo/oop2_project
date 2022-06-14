#include "StaticInclude\Teleport.h"

Teleport::Teleport(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE/1.2, BLOCK_SIZE/1.2), pos)
	{
	m_shape.setTexture(FileManager::instance().getSharedStaticTexture(TELEPORT));
	}
//------------------------------------------
//set the partner position

void Teleport::setPartnerPos(sf::Vector2f pos)
{
    m_Partner = pos;
}
//------------------------------------------
//close the teleport

void Teleport::toClose()
{
	m_isOpen = false;
}
//------------------------------------------
//return if the teleport is open

bool Teleport::isOpen()const
{
    return m_isOpen;
}

