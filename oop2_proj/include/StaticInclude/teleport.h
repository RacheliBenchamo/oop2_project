
#pragma once

#include "Board.h"
#include "StaticObj.h"
#include "Animation.h"



using std::vector;


class Teleport :public StaticObj
{
public:
	Teleport(sf::Vector2f pos);
	virtual void startSound()override;
	void setPartnerPos(sf::Vector2f);
	void toClose();
	bool isOpen();
	void toOpen() { m_isOpen = true; }
	sf::Vector2f getPertnetPos()const { return m_Partner; };

	
private:
	sf::Vector2f m_Partner;
	bool m_isOpen = true;

};




