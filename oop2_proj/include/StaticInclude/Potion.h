#pragma once
#include "StaticObj.h"

class Potion : public StaticObj
{
public:
	using StaticObj::StaticObj;

	virtual void startSound()override;
};