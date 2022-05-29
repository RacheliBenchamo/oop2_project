
#pragma once
#include "StaticObj.h"
#include "Animation.h"

using std::vector;


class StageDec :public StaticObj
{
public:
	//using StaticObj::StaticObj;
	StageDec(sf::Vector2f , levels, decoration,sf::Vector2f);

	//void update(const sf::Time& delta) override { m_animation.update(delta); };
	virtual void startSound() {};


private:

	sf::IntRect m_rect;
};




