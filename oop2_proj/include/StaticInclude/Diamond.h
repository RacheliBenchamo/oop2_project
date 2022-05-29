
#pragma once
#include "StaticObj.h"
#include "Animation.h"

using std::vector;


class Diamond :public StaticObj
{
public:
	//using StaticObj::StaticObj;
	Diamond(sf::Vector2f pos);
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	virtual void startSound()override;


private:

	Animation m_animation;
};




