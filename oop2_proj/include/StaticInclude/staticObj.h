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
		virtual void handleCollision(Wall&) override {};
		virtual void handleCollision(King&) override {};
		virtual void handleCollision(Warrior&) override {};
		virtual void handleCollision(Mage&) override {};
		virtual void handleCollision(Thief&) override {};
		virtual void handleCollision(Gate&) override {};
		virtual void handleCollision(Teleport&) override {};
		virtual void handleCollision(Ork&) override {};
		virtual void handleCollision(Throne&) override {};
		virtual void handleCollision(Fire&) override {};
		virtual void handleCollision(Gift&)override {};
		virtual void handleCollision(Key&)override {};
		virtual void handleCollision(Fairy&) override {};
private:
	bool m_replace;
	bool m_delete;
	};
