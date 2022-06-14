#pragma once
#include "MovingInclude\MovingObj.h"


class Monster :public MovingObj
{
public:
	Monster(const sf::Vector2f&, objects, sf::Vector2f , int,int );

	virtual void move(const sf::Time& delta, const sf::Vector2f)override;
	virtual void update(const sf::Time& delta) override { m_animation.update(delta); };

	void handleCollisionFloor(const GameObjBase& floor)override;
	void handleHit(const float_t);
	void hit();
	void pushFrom();
	void setPlayerPos(const sf::Vector2f pos) { m_playerPos = pos; }
	objects getMonNumber() const {return m_monsterNum;};

private:
	bool isPlayerClose();
	sf::Vector2f getMove();
	void randDir();
	void goAccordingToPlayerPos();

	sf::Vector2f m_playerPos{ 0,0 };
	sf::Vector2f m_lastDir= RIGHT_MOVEMENT;
	objects m_monsterNum= MONSTER1;
	Animation m_animation;
};

