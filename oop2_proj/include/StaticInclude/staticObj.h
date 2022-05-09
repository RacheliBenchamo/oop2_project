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
	    StaticObj(icons , int, int);
		virtual void startSound() = 0;
		virtual bool getToDelete()const;
		virtual void setDelete();
		virtual bool getToReplace()const;
		virtual void setReplace();

		virtual void handleCollision(GameObjBase&) override = 0;
private:
	bool m_replace;
	bool m_delete;
	};
