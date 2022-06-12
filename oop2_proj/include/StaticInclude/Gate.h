#pragma once
#include "StaticInclude\StaticObj.h"

class Gate : public StaticObj
{
public:
	Gate(sf::Vector2f pos)
		: StaticObj(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE * 2), pos)
	{
		m_shape.setTexture(FileManager::instance().getSharedStaticTexture(GATE));
		m_shape.setTextureRect(CLOSE_GATE_RECT);
	}
	void open()
	{
		m_isOpen = true;
		m_shape.setTextureRect(OPEN_GATE_RECT);
	}
	bool getIsOpen()const { return m_isOpen; };

private:
	bool m_isOpen =false;
};



