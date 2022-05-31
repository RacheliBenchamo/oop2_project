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
	void handelHit(int) ;
	void incPower() {};
	void addLife() { m_life + 100 > 1000 ? m_life = 1000 : m_life += 100 ;};
	void addPower() { m_power+200>1000? m_power=1000:m_power += 200; };
	void handleCollision(GameObjBase& floor)override;



private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();
	const sf::Vector2f getMovement(sf::Time& );
	void stayInPlaceAnimation(const sf::Vector2f& movement);

	int m_diamondsCount = 0;
	bool m_levelFinishStatus = false;
	int m_power=100;
	Animation m_animation;

};

