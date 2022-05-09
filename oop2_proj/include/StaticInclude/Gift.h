#pragma once
#include "StaticObj.h"

class Gift : public StaticObj
{
public:
	using StaticObj::StaticObj;

	virtual void startSound()override;
	virtual void handleCollision(GameObjBase&) override {};
};