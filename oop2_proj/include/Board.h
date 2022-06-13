#pragma once
#include "DataBase.h"

class DataBase;

class Board
{
public:
	Board();
	~Board() { };

	bool readLevelData(DataBase&,gender);
	void readLevel(DataBase &);
	sf::Vector2f getBoardSize()const { return m_boardSize; }
	void TakeBackInputStreamToBegLevel();
	void resetInputStream();
	void checkStageType(const char, DataBase&);
private:
	sf::Vector2f m_boardSize;
	std::ifstream m_input;
	int m_startOfTheLevel;
};
