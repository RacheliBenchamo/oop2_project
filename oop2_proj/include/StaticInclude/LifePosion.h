#pragma once
#include "StaticInclude\Potion.h"

class LifePotion : public Potion
{
public:
	LifePotion(sf::Vector2f pos)
		: Potion({ BLOCK_SIZE / 9,BLOCK_SIZE / 3 }, pos)
	{
		m_shape.setTexture(FileManager::instance().getSharedStaticTexture(POTION_L));
	}
private:
};
