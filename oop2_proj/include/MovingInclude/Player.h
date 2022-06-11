#pragma once
#include "MovingInclude\MovingObj.h"


class Player :public MovingObj
{
public:
	Player( const sf::Vector2f&,gender, int);
	virtual void move(sf::Time& ,sf::Vector2f)override;
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	void draw(sf::RenderWindow&)override;
	void handleFall(sf::Time& , sf::Vector2f );
	void handleJump(sf::Time& , bool , sf::Vector2f );
	void handelClimbing();
	void setHittingStatus(const bool status);
	void hit();
	void addDiamond() { m_diamondsCount++; };
	const int getDiamondsCount() const { return m_diamondsCount; }
	int getPower()const { return m_power; }
	void handleHit(int) ;
	void incPower() {};
	void addLife() { m_life + 100 > 1000 ? m_life = 1000 : m_life += 100 ;};
	void addPower() { m_power+200>1000? m_power=1000:m_power += 200; };
	void handleCollisionFloor(GameObjBase& floor)override;
	void handleCollisionLeftFloor(GameObjBase& floor) ;
	void handleCollisionRightFloor(GameObjBase& floor) ;
	void setClimbing(bool c) { m_climbing = c; }
	bool getClimbing() { return m_climbing; }
	bool m_wasClimbing = false;
	void setGotToNextLev() { m_gotToNextLev = true; };
	bool getGotToNextLev()const { return m_gotToNextLev; };

private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();
	const sf::Vector2f getMovement(sf::Time& );
	void stayInPlaceAnimation(const sf::Vector2f& movement);
	void startSound(sf::SoundBuffer* sound);
	bool m_climbing = false;
	int m_diamondsCount = 0;
	bool m_levelFinishStatus = false;
	int m_power=100;
	Animation m_animation;
	bool m_gotToNextLev = false;

};

