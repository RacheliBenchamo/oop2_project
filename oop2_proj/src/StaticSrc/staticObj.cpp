#include "StaticInclude\StaticObj.h"

//--------------------------------------------------
//constructor

StaticObj::StaticObj(icons icon, int i, int j)
:GameObjBase( icon,  i,  j), m_replace(false), m_delete(false)
{
	sf::Sprite sprite = getSprite();
	float x = getIconHeight();
	float y = sprite.getScale().y;
	sprite.scale(x, y);
	sprite.setScale(sf::Vector2f(((float)P_SIZE / getIconHeight()),
		((float)60 / getIconHeight())));

	setSprite(sprite);
}
//--------------------------------------------------

void StaticObj::setDelete()
{
	m_delete = true;
}
//--------------------------------------------------

bool StaticObj::getToReplace()const
{
	return m_replace;
}
//--------------------------------------------------

void StaticObj::setReplace()
{
	m_replace = true;
}
//--------------------------------------------------

bool StaticObj::getToDelete()const
{
	return m_delete;
}
