#include "Board.h"
//#include "DataBase.h"

//--------------------------------------------------
//constructor

Board::Board()
	: m_startOfPrevLevel(0), m_startOfTheLevel(0)
{
	this->m_input.open("Levels.txt", std::ios_base::in);

}
//-------------------------------------------------
//read the data of the level as size of the level and time
//limited for the level.
//return false in there is the end of the file

bool Board::readLevelData(DataBase& dataBase)
{
	if (m_input.eof())
		return false;

	int maxDimonds = 0;
	if (m_input.is_open())
	{
	

		if (m_startOfPrevLevel != 0)
			m_startOfPrevLevel = m_startOfTheLevel;

		m_startOfTheLevel = m_input.tellg();

		char c;
		m_input >> m_boardSize.x >> m_boardSize.y>> maxDimonds;
		m_input.get();
		dataBase.setLevelSize(m_boardSize.x, m_boardSize.y);
		dataBase.setLevelMaxDiamonds(maxDimonds);
	}

	return true;
}
//-------------------------------------------------
//read the objects on the current level from the levels text file
//and send each character to Database class to create it in the screen.

void Board::readLevel(DataBase& dataBase)
{
	if ((m_input).is_open())
	{
		int space_x = 100 , space_y = 60;
		char c;
		for (size_t i = 0; i < m_boardSize.x; i++)
		{
			for (size_t j = 0; j < m_boardSize.y; j++)
			{
				space_y += 40;
				c = char((m_input).get());
				if (c == EMPTY_C)
					continue;

				//std::cout <<i << " " << j << "\n";
				dataBase.setData(c,j+ space_y, i + space_x);
			}
			(m_input).get();
			space_x += 40;
			space_y = 100;
		}
	}
	//dataBase.FindTeleportPartner();
}
//--------------------------------------------------
//take the input stream to the begining of the curr level

void Board::TakeBackInputStreamToBegLevel()
{
	this->m_input.clear();
	m_input.seekg(m_startOfTheLevel);
}
//--------------------------------------------------
//take the input stream to the begining of the prev level

void Board::TakeBackInputStreamToPrevLevel()
{
	this->m_input.clear();
	m_input.seekg(m_startOfPrevLevel);
}
//--------------------------------------------------
//take the input stream to the begining of the text file

void Board::resetInputStream()
{
	this->m_input.clear();
	this->m_input.seekg(std::ios_base::beg);
}