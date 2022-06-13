#pragma once
#include "Board.h"
#include "StaticInclude\StaticObj.h"

class Teleport :public StaticObj
{
public:
	Teleport(sf::Vector2f pos);
	void setPartnerPos(sf::Vector2f);
	void toClose();
	bool isOpen()const;
	void toOpen() { m_isOpen = true; }
	sf::Vector2f getPertnetPos()const { return m_Partner; };

private:
	sf::Vector2f m_Partner;
	bool m_isOpen = true;

};




