#pragma once
#include "MovingInclude\MovingObj.h"


class Monster :public MovingObj
{
public:
	Monster(const sf::Vector2f&, icons, sf::Vector2f , int,int );
	void setPlayerPos(const sf::Vector2f pos) { m_playerPos = pos; }
	virtual void move(sf::Time& delta,sf::Vector2f)override ;
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	void hit();
	void handleFall() {};
	void handleHit(const float_t);
	void handleCollisionFloor(GameObjBase& floor)override;
	void pushFrom();
	monster getMonNumber() const {return monster(m_monsterNum);};

private:
	bool isPlayerClose();
	sf::Vector2f getMove();
	void randDir();
	void goAccordingToPlayerPos();

	sf::Vector2f m_playerPos{ 0,0 };
	sf::Vector2f m_lastDir= RIGHT_MOVEMENT;
	int m_monsterNum;
	Animation m_animation;

};

