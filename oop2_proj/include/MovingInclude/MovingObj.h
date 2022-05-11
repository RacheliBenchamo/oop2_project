#pragma once
#include "GameObjBase.h"
#include "Animation.h"


class Controller;

class MovingObj : public GameObjBase
{
public:
	using GameObjBase::GameObjBase;
	~MovingObj() {};

	sf::Vector2f getPrevPos() const{ return m_prevPos; }
	sf::Vector2f getCurrDir()const { return m_currDirection; }
	void backToPrevPos();
	virtual void handleCollision(GameObjBase&) override =0;
	

protected:

	sf::Vector2f getDirection() const;
	bool outWindow(sf::Vector2f, sf::Vector2f) const;
	void updateAnimation();
	virtual void move(sf::Time&, sf::Vector2f ) {};
	void setPrevPos(sf::Vector2f p) { m_prevPos = p; }
	void setCurrDir(sf::Vector2f d) { m_currDirection = d; }

private:
	void updateSpriteCol();

	sf::Vector2f m_prevPos;	
	sf::Vector2f m_currDirection;
	int m_animationRow;
	int m_animationCol;

	Animation m_animation;
	int m_life;
};