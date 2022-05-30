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
class Floor;



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
	void setDisappear(bool);

	virtual bool getToDelete()const;
    void setToDelete();
	bool getToReplace()const;
	void setToReplace();

protected:
	sf::RectangleShape m_shape;
	void setScale(const sf::Vector2f& scale) {m_shape.setScale(scale);}
private:
	bool m_disappear = false;
	bool m_replace = false;
	bool m_delete = false;
};

