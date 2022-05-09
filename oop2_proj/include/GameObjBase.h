#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <memory>
#include<stdio.h>
#include <fstream>
#include "FileManager.h"

class King;
class Warrior;
class Mage;
class Thief;
class Ork;
class Gate;
class Throne;
class Teleport;
class Fire;
class Key;
class Wall;
class Gift;
class Fairy;


class GameObjBase
{
public:
	GameObjBase() {};
	GameObjBase(icons , int, int);
	virtual ~GameObjBase() {};

	sf::Sprite getSprite() const{ return m_sprite; }
	void setSprite(sf::Sprite sprite) { m_sprite = sprite;  }
	virtual void draw(sf::RenderWindow& );
	virtual bool checkCollision(const GameObjBase& );
	sf::Vector2f getPos() const;
	void setPos(const sf::Vector2f&);
	float getIconWidth() const;
	float getIconHeight() const;
	sf::Vector2f getScale() const;
	
	virtual void handleCollision(GameObjBase& )  = 0;

	

private:
	sf::Sprite m_sprite;
};

