#include "Board.h"
//#include "DataBase.h"

//--------------------------------------------------
//constructor

Board::Board()
	: m_startOfTheLevel(0)
{
	this->m_input.open("Levels.txt", std::ios_base::in);
	if (!(m_input.is_open()))
	{
		throw std::iostream::failure("File: Levels.txt doesnt exist\n");
	}
}
//-------------------------------------------------
//read the data of the level as size of the level and time
//limited for the level.
//return false in there is the end of the file

bool Board::readLevelData(DataBase& dataBase, gender g)
{
	dataBase.setGender(g);
	if (m_input.eof())
		return false;

	int maxDimonds = 0;
	
	char c = 'F';
	if (m_input.is_open())
	{
		m_startOfTheLevel = m_input.tellg();

		char c;
		m_input >> m_boardSize.x >> m_boardSize.y>> c;
		m_input.get();
		dataBase.setLevelSize(m_boardSize.x, m_boardSize.y);
		checkStageType(c, dataBase);
		//dataBase.setLevelMaxDiamonds(maxDimonds);
	}

	return true;
}
//-------------------------------------------------
//read the objects on the current level from the levels text file
//and send each character to Database class to create it in the screen.

void Board::readLevel(DataBase& dataBase)
{
	int space_x = START_SPACE,
		space_y = START_SPACE- Y_SPACE;
	char c;

	if ((m_input).is_open())
	{
		for (size_t i = 0; i < m_boardSize.x; i++)
		{
			for (size_t j = 0; j < m_boardSize.y; j++)
			{
				space_y += Y_SPACE;
				c = char((m_input).get());
				if (c == EMPTY_C)
					continue;
				dataBase.setData(c,j+ space_y, i + space_x);
			}
			(m_input).get();
			space_x += X_SPACE;
			space_y = START_SPACE;
		}
	}
	dataBase.FindTeleportPartner();
}
//--------------------------------------------------
//take the input stream to the begining of the curr level

void Board::TakeBackInputStreamToBegLevel()
{
	this->m_input.clear();
	m_input.seekg(m_startOfTheLevel);
}
//--------------------------------------------------
//take the input stream to the begining of the text file

void Board::resetInputStream()
{
	this->m_input.clear();
	this->m_input.seekg(std::ios_base::beg);
}

void Board::checkStageType(const char c, DataBase& dataBase)
{
	switch (c)
	{
	case 'F':
		dataBase.setStageType(FOREST);
		break;
	case 'S':
		dataBase.setStageType(SNOW);
		break;
	case 'D':
	default:
		dataBase.setStageType(DESERT);
		break;

	}
}
