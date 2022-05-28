#pragma once
#include "MovingInclude\MovingObj.h"


class Monster :public MovingObj
{
public:
	Monster(const sf::Vector2f&, levels, icons, sf::Vector2f);

	virtual void move(sf::Time& delta,sf::Vector2f)override {};
	virtual void move(sf::Time&);
	void update(const sf::Time& delta) override { m_animation.update(delta); };

	void handleFall() {};
	int getForce()const { return m_force; }
	virtual void handleCollision(GameObjBase&) override {};


private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();

	int m_force = 10;
	Animation m_animation;

};

