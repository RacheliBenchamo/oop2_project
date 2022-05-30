#pragma once
#include "Gift.h"
#include "Animation.h"
class PowerPosion : public Posion
{
public:
	//using Posion::Posion;
	PowerPosion(sf::Vector2f pos);
	~PowerPosion() {};

	void update(const sf::Time& delta) override { m_animation.update(delta); };
	virtual void startSound()override;


private:

	Animation m_animation;
};







