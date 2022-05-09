
#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Board.h"
#include "StaticObj.h"


using std::vector;


class Teleport :public StaticObj
{
public:
	using StaticObj::StaticObj;

	virtual void startSound()override;
	void setPartnerPos(sf::Vector2f);
	void toClose() { m_isOpen = false; }
	bool isOpen();
	void toOpen() { m_isOpen = true; }

	void handleCollision(GameObjBase&) override;
	
private:
	sf::Vector2f m_Partner;
	bool m_isOpen = true;
};




