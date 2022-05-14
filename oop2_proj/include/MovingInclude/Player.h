#pragma once
#include "MovingInclude\MovingObj.h"


class Player :public MovingObj
{
public:
	Player( const sf::Vector2f& );
	virtual void move(sf::Time&, sf::Vector2f)override {};
	virtual void move(sf::Time&);
	void update(const sf::Time& delta) override { m_animation.update(delta); };

	void handleFall() {};
	void handleJump(bool) {};
	void shoot() {};
	void addDiamond() {};
	const int getDiamondsCount() const {};
	bool isFinishedLevel(const int) {};
	void incLife() {};
	void incPower() {};
	void addLife() {};
	void addPower() {};
	virtual void handleCollision(GameObjBase&) override {};


private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();

	int m_diamondsCount = 0;
	bool m_levelFinishStatus = false;
	int m_power;
	Animation m_animation;

};

