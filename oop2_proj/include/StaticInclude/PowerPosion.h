#pragma once
#include "Posion.h"
#include "Animation.h"
#include "StaticObj.h"
class PowerPosion : public Posion
{
public:
	//using Posion::Posion;
	PowerPosion(sf::Vector2f pos)
		: Posion({ BLOCK_SIZE/9,BLOCK_SIZE/3 }, pos)
	{m_shape.setTexture(FileManager::instance().getSharedStaticTexture(POTION_P));}

	~PowerPosion() {};

	virtual void startSound() {};


private:
};







