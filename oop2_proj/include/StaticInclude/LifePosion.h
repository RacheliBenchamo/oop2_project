#pragma once
#include "Posion.h"
#include "Animation.h"

class LifePosion : public Posion
{
public:
	LifePosion(sf::Vector2f pos)
		: Posion({ BLOCK_SIZE / 9,BLOCK_SIZE / 3 }, pos)
	{m_shape.setTexture(FileManager::instance().getSharedStaticTexture(POTION_L));}

	~LifePosion() {};
	virtual void startSound() {};

private:
};
