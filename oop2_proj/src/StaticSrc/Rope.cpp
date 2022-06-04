
#include "StaticInclude\Rope.h"

Rope::Rope(sf::Vector2f pos)
	: StaticObj(sf::Vector2f(BLOCK_SIZE/3 , BLOCK_SIZE*2), pos)
{
	m_shape.setTexture(FileManager::instance().getSharedStaticTexture(ROPE));
}
//--------------------------------------------------

void Rope::startSound()
{

}