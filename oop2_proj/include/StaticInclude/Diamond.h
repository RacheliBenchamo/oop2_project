#pragma once
#include "StaticInclude\StaticObj.h"

class Diamond :public StaticObj
{
public:
	Diamond(sf::Vector2f pos);
	void update(const sf::Time& delta) override { m_animation.update(delta); };

private:
	Animation m_animation;
};




