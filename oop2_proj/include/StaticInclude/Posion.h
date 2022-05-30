#pragma once
#include "StaticObj.h"

class Posion : public StaticObj
{
public:
	using StaticObj::StaticObj;

	virtual void startSound()override;
};