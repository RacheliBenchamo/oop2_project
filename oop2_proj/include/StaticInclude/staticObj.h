#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <memory>
#include<stdio.h>
#include <fstream>
#include <GameObjBase.h>



class StaticObj :public GameObjBase
{
public:
	using GameObjBase::GameObjBase;

		virtual void startSound() = 0;

		virtual void handleCollision(GameObjBase&) override = 0;
private:
	};
