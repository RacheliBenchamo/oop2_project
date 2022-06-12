#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <memory>
#include<stdio.h>
#include <fstream>
#include "FileManager.h"

class Teleport;

class GameObjBase
{
public:
	GameObjBase(const sf::Vector2f& , const sf::Vector2f& );
	virtual ~GameObjBase() {};

	sf::RectangleShape getShape() const{ return m_shape; }
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

