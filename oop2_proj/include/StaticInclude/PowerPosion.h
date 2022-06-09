#pragma once
#include "Potion.h"
#include "Animation.h"
#include "StaticObj.h"
class PowerPotion : public Potion
{
public:
	//using Posion::Posion;
	PowerPotion(sf::Vector2f pos)
		: Potion({ BLOCK_SIZE/9,BLOCK_SIZE/3 }, pos)
	{m_shape.setTexture(FileManager::instance().getSharedStaticTexture(POTION_P));}

	~PowerPotion() {};

	virtual void startSound() {};


private:
};







