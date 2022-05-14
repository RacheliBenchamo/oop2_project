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
	GameObjBase(const sf::Vector2f& , const sf::Vector2f& );
	virtual ~GameObjBase() {};

	sf::RectangleShape getShape() const{ return m_shape; }
	void setShape(sf::RectangleShape shape) { m_shape = shape; }
	virtual void draw(sf::RenderWindow& );
	virtual bool checkCollision(const GameObjBase& );
	sf::Vector2f getPos() const;
	void setPos(const sf::Vector2f&);
	float getIconWidth() const;
	float getIconHeight() const;
	sf::Vector2f getScale() const;
	
	virtual void handleCollision(GameObjBase& )  = 0;

	virtual bool getToDelete()const;
	virtual void setDelete();
	virtual bool getToReplace()const;
	virtual void setReplace();

protected:
	sf::RectangleShape m_shape;
	void setScale(const sf::Vector2f& scale) {m_shape.setScale(scale);}
private:
	bool m_replace;
	bool m_delete;
};

