#pragma once
#include "StaticInclude\Potion.h"

class PowerPotion : public Potion
{
public:
	PowerPotion(sf::Vector2f pos)
		: Potion({ BLOCK_SIZE/9,BLOCK_SIZE/3 }, pos)
	{
		m_shape.setTexture(FileManager::instance().getSharedStaticTexture(POTION_P));
	}
private:
};







