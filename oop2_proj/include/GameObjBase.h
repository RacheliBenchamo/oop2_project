#pragma once
#include "FileManager.h"

class Teleport;

class GameObjBase
{
public:
	GameObjBase(const sf::Vector2f& , const sf::Vector2f& );
	virtual ~GameObjBase() {};

	virtual void draw(sf::RenderWindow&);
	virtual bool checkCollision(const GameObjBase&);

	sf::RectangleShape getShape() const{ return m_shape; }
	sf::Vector2f getPos() const;
	void setPos(const sf::Vector2f&);
	sf::Vector2f getScale() const;
	bool getToDelete()const;
    void setToDelete();
	bool getToReplace()const;
	void setToReplace();

protected:

	sf::RectangleShape m_shape;

private:
	bool m_replace = false;
	bool m_delete = false;
};

