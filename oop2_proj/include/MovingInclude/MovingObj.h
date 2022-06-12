#pragma once
#include "GameObjBase.h"
#include "Animation.h"

class Controller;

class MovingObj : public GameObjBase
{
public:
	MovingObj(const sf::Vector2f& , const sf::Vector2f& ,int);

	virtual void move(const sf::Time&,const sf::Vector2f) = 0;
	virtual void handleCollisionFloor(const GameObjBase& floor) = 0;

	int getLife()  const { return m_life; }
	bool getHitingStatus() const { return m_hitingStatus; }
	levels getCurrLevel() const { return levels(m_level); }
	float getDamage()const { return m_force; }
	bool toPrintDamage() const { return m_hurt; }
	void printDamage(sf::RenderWindow& window)const;
	void setHurt(const bool isHurt) { m_hurt = isHurt; }

protected:
	bool collisionFromLeft(const GameObjBase& g) const;
	bool collisionFromRight(const GameObjBase& g) const;
	bool collisionFromBelow(const GameObjBase& g) const;
	bool CollisionFromAboveFloor(const GameObjBase& floor) const;
	bool CollisionFromAboveLeftFloor(const GameObjBase& floor) const;
	bool CollisionFromAboveRightFloor(const GameObjBase& floor) const;

	virtual void update(const sf::Time&) {}
	sf::Vector2f getPrevPos() const { return m_prevPos; }
	sf::Vector2f getCurrDir()const { return m_currDirection; }
	void backToPrevPos();
	bool onFloor() const { return m_onFloor; };
	void setCurrLevel(const int level) { m_level = level; }
	void setDamagePos(const sf::Vector2f pos);
	void setDamageString(const int);
	sf::Vector2f getDirection() const;
	bool outWindow(const sf::Vector2f, const sf::Vector2f) const;
	void setPrevPos(const sf::Vector2f p) { m_prevPos = p; }
	void setCurrDir(const sf::Vector2f d) { m_currDirection = d; }
	bool isAlive() const { return m_life > int(0); };

	int m_life;
	float m_force;

	bool m_right,m_left ,
		m_onFloor ,m_inHnaldeJump ,
		m_inHandleFall,m_hitingStatus,
		m_falling ,m_up ,m_down;

private:
	bool m_hurt = false;
	void updateSpriteCol();
	void setDamage();
	int m_level;
	sf::Text m_damage;
	sf::Vector2f m_prevPos;	
	sf::Vector2f m_currDirection;

};