#pragma once
#include "MovingInclude\MovingObj.h"


class Player :public MovingObj
{
public:
	using MovingObj::MovingObj;
	virtual void move(sf::Time&, sf::Vector2f)override;

	void handleFall() {};
	void handleJump(bool) {};
	void shoot() {};
	void addDiamond() {};
	const int getDiamondsCount() const {};
	bool isFinishedLevel(const int) {};
	const bool isAlive() const {};
	void incLife() {};
	void incPower() {};
	void addLife() {};
	void addPower() {};

private:
	int m_diamondsCount = 0;
	bool m_levelFinishStatus = false;
	int m_power;
};

