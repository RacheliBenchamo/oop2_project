
#pragma once

#include "Board.h"
#include "StaticObj.h"
#include "Animation.h"



using std::vector;


class Teleport :public StaticObj
{
public:
	//using StaticObj::StaticObj;
	Teleport(sf::Vector2f pos);
	virtual void startSound()override;
	void setPartnerPos(sf::Vector2f);
	void toClose() { m_isOpen = false; }
	bool isOpen();
	void toOpen() { m_isOpen = true; }


	void update(const sf::Time& delta) override {m_animation.update(delta);};

	
private:
	Animation m_animation;
	sf::Vector2f m_Partner;
	bool m_isOpen = true;

};




