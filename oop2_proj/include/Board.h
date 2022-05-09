#pragma once
#include <array>
#include <fstream>
#include<stdio.h>
#include <iostream>
#include "DataBase.h"

class DataBase;

class Board
{
public:
	Board();
	~Board() {};

	bool readLevelData(DataBase&);
	void readLevel(DataBase &);
	sf::Vector2f getBoardSize()const { return m_boardSize; }
	int getLevelTime() const { return m_timeLimit; }
	void TakeBackInputStreamToBegLevel();
	void TakeBackInputStreamToPrevLevel();
	void resetInputStream();

private:

	sf::Vector2f m_boardSize;
	std::ifstream m_input;
	int m_timeLimit;
	int m_startOfTheLevel;
	int m_startOfPrevLevel;

};
