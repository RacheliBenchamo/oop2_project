#pragma once
#include "StaticInclude\StaticObj.h"

class StageDec :public StaticObj
{
public:
	StageDec(sf::Vector2f , levels, decoration,sf::Vector2f);
private:
	sf::IntRect m_rect;
};




