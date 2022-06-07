#pragma once
#include "StaticObj.h"

class Gate : public StaticObj
{
public:
	//using StaticObj::StaticObj;
	Gate(sf::Vector2f pos)
		: StaticObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE * 2), pos)
	{
		m_shape.setTexture(FileManager::instance().getSharedStaticTexture(GATE));
		m_shape.setTextureRect(CLOSE_GATE_RECT);
	}
	bool getIsOpen()const { return m_isOpen; };
	void open()
	{
		m_isOpen = true;
		m_shape.setTextureRect(OPEN_GATE_RECT);
	}
	virtual void startSound()override { ; }

private:
	bool m_isOpen =false;
};



