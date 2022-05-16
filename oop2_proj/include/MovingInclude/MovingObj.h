#pragma once
#include "GameObjBase.h"
#include "Animation.h"


class Controller;

class MovingObj : public GameObjBase
{
public:
	using GameObjBase::GameObjBase;

	sf::Vector2f getPrevPos() const{ return m_prevPos; }
	sf::Vector2f getCurrDir()const { return m_currDirection; }
	void backToPrevPos();
	virtual void handleCollision(GameObjBase&) override =0;
	virtual void update(const sf::Time&) {};
	int getLife()  const { return m_life; }

protected:

	sf::Vector2f getDirection() const;
	bool outWindow(sf::Vector2f, sf::Vector2f) const;
	void updateAnimation();
	virtual void move(sf::Time&, sf::Vector2f ) {};
	void setPrevPos(sf::Vector2f p) { m_prevPos = p; }
	void setCurrDir(sf::Vector2f d) { m_currDirection = d; }
	bool isAlive() const {return m_life> 0;}


	int m_life=100;
	bool mvRight = false,
		 mvLeft = false;
private:
	void updateSpriteCol();

	sf::Vector2f m_prevPos;	
	sf::Vector2f m_currDirection;
	int m_animationRow;
	int m_animationCol;
};