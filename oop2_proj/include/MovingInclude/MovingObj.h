#pragma once
#include "GameObjBase.h"

class Controller;

class MovingObj : public GameObjBase
{
public:
	MovingObj(icons, int, int);
	~MovingObj() {};

	sf::Vector2f getPrevPos() const{ return m_prevPos; }
	sf::Vector2f getCurrDir()const { return m_currDirection; }
	void backToPrevPos();
	virtual void handleCollision(GameObjBase&) override =0;
	virtual void handleCollision(Wall&) override {};
	virtual void handleCollision(King&) override {};
	virtual void handleCollision(Warrior&) override {};
	virtual void handleCollision(Mage&) override {};
	virtual void handleCollision(Thief&) override {};
	virtual void handleCollision(Gate&) override {};
	virtual void handleCollision(Teleport&) override {};
	virtual void handleCollision(Ork&) override {};
	virtual void handleCollision(Throne&) override {};
	virtual void handleCollision(Fire&) override {};
	virtual	void handleCollision(Key&) override {};
	virtual void handleCollision(Gift&)override {};
	virtual void handleCollision(Fairy&) override {};

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



};