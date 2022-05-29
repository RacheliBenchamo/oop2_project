#pragma once
#include "MovingInclude\MovingObj.h"


class Player :public MovingObj
{
public:
	Player( const sf::Vector2f& );
	virtual void move(sf::Time& ,sf::Vector2f)override;
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	void draw(sf::RenderWindow&)override;
	void handleFall(sf::Time& , sf::Vector2f );
	void handleJump(sf::Time& , bool , sf::Vector2f );
	void setHittingStatus(const bool status);
	void hit();
	void addDiamond() { m_diamondsCount++; };
	const int getDiamondsCount() const { return m_diamondsCount; }
	bool isFinishedLevel(const int) {};
	int getPower()const { return m_power; }
	void incLife() {};
	void incPower() {};
	void addLife() {};
	void addPower() {};


private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();
	const sf::Vector2f getMovement(sf::Time& );
	void stayInPlaceAnimation(const sf::Vector2f& movement);
	void handleCollision(GameObjBase& floor)override;

	int m_diamondsCount = 0;
	bool m_levelFinishStatus = false;
	int m_power=100;
	Animation m_animation;

};

