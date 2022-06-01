#pragma once
#include "MovingInclude\MovingObj.h"


class Monster :public MovingObj
{
public:
	Monster(const sf::Vector2f&, levels, icons, sf::Vector2f,int);
	void setPlayerPos(const sf::Vector2f pos) { m_playerPos = pos; }
	virtual void move(sf::Time& delta,sf::Vector2f)override ;
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	void hit();
	void handleFall() {};
	void setOperation(const Operation );
	void handleHit();
	void handleCollision(GameObjBase& floor)override;
	void pushFrom();


private:
	bool isPlayerClose();
	void scaleAccordingToPlayerPos();
	sf::Vector2f getMove();
	void grillDir();
	void goAccordingToPlayerPos();


	void playDeathSound() const {};
	void playHurtSound() const {};
	void playAttackSound() const {};

	sf::Vector2f m_playerPos{ 0,0 };
	sf::Vector2f m_lastDir= RIGHT_MOVEMENT;
	Animation m_animation;

};

