#pragma once
#include "Posion.h"
#include "Animation.h"
#include "StaticObj.h"
class PowerPosion : public Posion
{
public:
	//using Posion::Posion;
	PowerPosion(sf::Vector2f pos)
		:Posion(sf::Vector2f(BLOCK_SIZE / 4, BLOCK_SIZE / 6), pos),
		m_animation
		(FileManager::p2FileManager().getStaticData(DIAMOND),
			Stay,
			m_shape,
			FileManager::p2FileManager().getSharedStaticTexture(DIAMOND))
	{
		m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getSize().y / 2);
		m_shape.setOrigin(m_shape.getOrigin().x, m_shape.getOrigin().y + m_shape.getSize().y / 2);
		m_shape.scale(1, 2.2f);
	}

	~PowerPosion() {};

	void update(const sf::Time& delta) override { m_animation.update(delta); };
	virtual void startSound() {};


private:

	Animation m_animation;
};







