#pragma once
#include "MovingInclude\MovingObj.h"


class Player :public MovingObj
{
public:
	Player( const sf::Vector2f&,gender, int);

	virtual void move(const sf::Time& , const sf::Vector2f)override;
	void update(const sf::Time& delta) override { m_animation.update(delta); };
	void draw(sf::RenderWindow&)override;

	void handleCollisionFloor(const GameObjBase& floor)override;
	void handleCollisionLeftFloor(const GameObjBase& floor);
	void handleCollisionRightFloor(const GameObjBase& floor);
	void handleFall(const sf::Time& , const sf::Vector2f );
	void handleJump(const sf::Time& , const bool , const sf::Vector2f );
	void handleClimbing();
	void handleHit(const float_t);
	void hit();

	void setHittingStatus(const bool status);
	void addDiamond() { m_diamondsCount++; };
	int getDiamondsCount() const { return m_diamondsCount; }
	int getPower()const { return m_power; }
	void addLife() { m_life + ADD_LIFE > MAX_LIFE ? m_life = MAX_LIFE : m_life += ADD_LIFE;};
	void addPower() { m_power+ ADD_POWER > MAX_POWER ? m_power= MAX_POWER :m_power += ADD_POWER; };
	
	void setClimbing(const bool c) { m_climbing = c; }
	bool getClimbing()const { return m_climbing; }
	void setGotToNextLev() { m_gotToNextLev = true; };
	bool getGotToNextLev()const { return m_gotToNextLev; };

private:
	void setMovementStatus(const sf::Vector2f& movement);
	void playMovementAnimations();
	const sf::Vector2f getMovement(const sf::Time& );
	void stayInPlaceAnimation(const sf::Vector2f& movement);
	void startSound(sf::SoundBuffer* sound);

	bool m_climbing = false;
	int m_diamondsCount = 0;
	int m_power= MAX_POWER;
	Animation m_animation;
	bool m_gotToNextLev = false;

};

