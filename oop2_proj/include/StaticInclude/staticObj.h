#pragma once
#include <GameObjBase.h>
#include "Animation.h"

class StaticObj :public GameObjBase
{
public:
	using GameObjBase::GameObjBase;
	virtual void update(const sf::Time&) {};
private:
	};
