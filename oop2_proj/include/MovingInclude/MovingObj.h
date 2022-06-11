#pragma once
#include "GameObjBase.h"
#include "Animation.h"


class Controller;

class MovingObj : public GameObjBase
{
public:
	//using GameObjBase::GameObjBase;
	MovingObj(const sf::Vector2f& , const sf::Vector2f& ,int);
	sf::Vector2f getPrevPos() const{ return m_prevPos; }
	sf::Vector2f getCurrDir()const { return m_currDirection; }
	void backToPrevPos();
	virtual void update(const sf::Time&) {}
	int getLife()  const { return m_life; }
	int getForce()const { return m_force; }
	bool getHitingStatus() const { return m_hitingStatus; }
	void beHurt() ;
	bool onFloor() const{ return m_onFloor; };
	virtual void handleCollisionFloor(GameObjBase& floor)=0;

	levels getCurrLevel() const { return levels(m_level); }
	void setCurrLevel(const int level) { m_level = level; }
	void setDamagePos(const sf::Vector2f pos);
	void printDamage(sf::RenderWindow& window)const;
	void setDamageString();
	void setHurt(const bool isHurt) { m_hurt = isHurt; }
	bool toPrintDamage() const { return m_hurt; }
protected:
	bool collisionFromLeft(GameObjBase& g) const;
	bool collisionFromRight(GameObjBase& g) const;
	bool collisionFromBelow(GameObjBase& g) const;
	bool CollisionFromAboveFloor(GameObjBase& floor) const;
	bool CollisionFromAboveLeftFloor(GameObjBase& floor) const;
	bool CollisionFromAboveRightFloor(GameObjBase& floor) const;
	


	sf::Vector2f getDirection() const;
	bool outWindow(sf::Vector2f, sf::Vector2f) const;
	void updateAnimation();
	virtual void move(sf::Time& , sf::Vector2f ) {};
	void setPrevPos(sf::Vector2f p) { m_prevPos = p; }
	void setCurrDir(sf::Vector2f d) { m_currDirection = d; }
	bool isAlive() const { return m_life > int(0); };

	int m_life;
	int m_force;

	bool m_right,m_left ,
		m_onFloor ,m_inHnaldeJump ,
		m_inHandleFall,m_hitingStatus,
		m_falling ,m_up ,m_down;

private:
	bool m_hurt;
	void updateSpriteCol();
	void setDamage();
	int m_level;
	sf::Text m_damage;
	sf::Vector2f m_prevPos;	
	sf::Vector2f m_currDirection;

};