#include "DataBase.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

DataBase::DataBase()
	:m_currPlayer(KING), m_GiftsWithTime(false), m_currTeleport(0)
{
	resetTakeGifts();
	m_movingRec.setSize(sf::Vector2f((float)32, (float)32 / 15));
	m_movingRec.setFillColor(sf::Color(255, 255, 0, 250));
}

//---------------------------------------------------

void DataBase::setLevelSize(int x, int y)
{
	m_levelSize.x = x;
	m_levelSize.y = y;
}
//---------------------------------------------------
//create all the object in the level

void DataBase::setData(char c, int i, int j)
{
		if(!createStaticObj(c, j, i))
		createMovingObj(c, j, i);
}
//-----------------------------------------------------------
//create all the moving object in the level

void DataBase::createMovingObj(const char c, const size_t i,
	const size_t j)
{
	switch (c)
	{
	case KING_C:
		m_players[KING] = (std::make_unique<King>(KING, i, j));
		break;

	case WARRIOR_C:
		m_players[WARRIOR] = (std::make_unique<Warrior>(WARRIOR, i, j));
		break;

	case THIEF_C:
		m_players[THIEF] = (std::make_unique<Thief>(THIEF, i, j));
		break;

	case MAGE_C:
		m_players[MAGE] = (std::make_unique<Mage>(MAGE, i, j));
		break;

	case FAIRY_C:
		//cout << "add fairies" << i << " " << j << " \n";
		m_fairies.push_back(std::make_unique<Fairy>((FAIRY), i, j));
		break;
	}
}
//-----------------------------------------------
//create all the static object in the level

bool DataBase::createStaticObj(const char c, const size_t i,
	const size_t j)
{
	switch (c)
	{
	case ORK_C:
		m_staticsObj.push_back(std::make_unique<Ork>((ORK), i, j));
		return true;
		break;
	case FIRE_C:
		m_staticsObj.push_back(std::make_unique<Fire>((FIRE), i, j));
		return true;
		break;
	case GATE_C:
		m_staticsObj.push_back(std::make_unique<Gate>((GATE), i, j));
		return true;
		break;
	case TELEPORT_C:
		m_teleport.push_back(std::make_unique<Teleport>((TELEPORT), i, j));
		return true;
		break;
	case THRONE_C:
		m_staticsObj.push_back(std::make_unique<Throne>((THRONE), i, j));
		return true;
		break;
	case WALL_C:
		m_staticsObj.push_back(std::make_unique<Wall>((WALL), i, j));
		return true;
		break;
	case KEY_C:
		m_staticsObj.push_back(std::make_unique<Key>((KEY), i, j));
		return true;
		break;
	case GIFT_C:
		m_staticsObj.push_back(grillGiftType((GIFT), i, j));
		return true;
		break;
	default:
		return false;
		break;
	}
}
//-----------------------------------------------
//draw all the object in the level on the window

void DataBase::draw(sf::RenderWindow& window)
{
	drawStaticObj(window);
	drawMovingObj(window);
	window.draw(m_movingRec);
}
//-----------------------------------------------
//draw all the static object in the level on the window

void DataBase::drawStaticObj(sf::RenderWindow& window)
{
	for (auto& e : m_staticsObj)
		e->draw(window);

	for (auto& e : m_teleport)
		e->draw(window);
}
//---------------------------------------------------
//draw all the moving object in the level on the window

void DataBase::drawMovingObj(sf::RenderWindow& window)
{
	for (auto& e : m_players)
		e->draw(window);

	for (auto& e : m_fairies)
		e->draw(window);
}
//--------------------------------------------------------------
//find the partner of the teleports

void DataBase::FindTeleportPartner() const
{
	for (int index = 0; index < m_teleport.size(); index++)
	{
		if (index % 2 == 0)
			m_teleport[index]->setPartnerPos(m_teleport[index + 1]->getPos());
		else
			m_teleport[index]->setPartnerPos(m_teleport[index - 1]->getPos());
	}
}
//--------------------------------------------------
//switch the current player to other player

void DataBase::switchPlayer()
{
	if (m_currPlayer == KING)
		m_currPlayer = MAGE;
	else if (m_currPlayer == MAGE)
		m_currPlayer = WARRIOR;
	else if (m_currPlayer == WARRIOR)
		m_currPlayer = THIEF;
	else if (m_currPlayer == THIEF)
		m_currPlayer = KING;
}
//--------------------------------------------------
//handle the moving in this moment

void DataBase::move(sf::Time deltaTime)
{
	//move faireis
	for (auto& f : m_fairies)
		f->move(deltaTime, m_levelSize);

	//move current player
	m_players[m_currPlayer]->move(deltaTime, m_levelSize);
	handelCollisions();

	//	moving rect to tell who is the choosen character
	m_movingRec.setPosition(m_players[m_currPlayer]->getPos().x,
		m_players[m_currPlayer]->getPos().y + 60);
	m_movingRec.setScale(m_players[m_currPlayer]->getScale());
}
//-------------------------------------------------
//handle the collisions in this moment

void DataBase::handelCollisions()
{
	handelPlayerCollisions();
	handelFairiesCollisions();
	handelTeleportCollisions();
	deleteRelevantObj();
}
//----------------------------------------------------
//handle the current player collisions in this moment

void DataBase::handelPlayerCollisions()
{
	// check collition with static object
	for (auto& p : m_staticsObj)
		if (m_players[m_currPlayer]->checkCollision(*p))
			m_players[m_currPlayer]->handleCollision(*p);
	
	for (auto& p : m_players)
		if (m_players[m_currPlayer]->checkCollision(*p))
			m_players[m_currPlayer]->handleCollision(*p);
}
//----------------------------------------------------
 //handle the fairies collisions in this moment

void DataBase::handelFairiesCollisions()
{
	for (auto& f : m_fairies)
	{
		for (auto& p : m_players)
			if (f->checkCollision(*p))
				f->handleCollision(*p);

		for (auto& c : m_staticsObj)
			if (f->checkCollision(*c))
				f->handleCollision(*c);

		for (auto& fa : m_fairies)
			if (f != fa)
				if (f->checkCollision(*fa))
					f->handleCollision(*fa);
	}
}
//----------------------------------------------------
//handle the teleports collisions in this moment

void DataBase::handelTeleportCollisions()
{
	for (int index = 0; index < m_teleport.size(); index++)
	{
		if (!(m_players[m_currPlayer]->checkCollision(*m_teleport[m_currTeleport])))
			m_teleport[m_currTeleport]->toOpen();

		if (m_players[m_currPlayer]->checkCollision(*m_teleport[index])
			&& m_teleport[index]->isOpen())
		{
			if (index % 2 == 0)
				itsAllowedToEnterTheTeleport(index , 1);
			else
				itsAllowedToEnterTheTeleport(index , -1);
		}
	}
}
//-----------------------------------------------------
//check if its allowed to enter the teleport

void DataBase::itsAllowedToEnterTheTeleport(int place,int move)
{
	if (m_teleport[place + move]->isOpen() && ThereIsNoObjectOnTheMemberTel(place + move))
	{
		m_teleport[place + move]->toClose();
		m_currTeleport = place + move;
		m_players[m_currPlayer]->handleCollision(*m_teleport[place]);
	}
}
//-----------------------------------------------------
//check if there is no object on the member teleport

bool DataBase::ThereIsNoObjectOnTheMemberTel(int index)
{
	for (auto& p : m_players)
		if (p->checkCollision(*m_teleport[index]))
			return false;

	for (auto& fa : m_fairies)
		if (fa->checkCollision(*m_teleport[index]))
			return false;

	return true;
}
//-----------------------------------------------------
//delete the relevant Objects from the level

void DataBase::deleteRelevantObj()
{
	replaceOrkWithKey();
	takeGift();
	std::erase_if(m_staticsObj, [](const auto& object) {return object->getToDelete(); });
}
//-----------------------------------------------------
//replace the orks that killed with key sprite

void DataBase::replaceOrkWithKey()
{
	for (int i = 0; i < m_staticsObj.size(); i++)
	{
		if (m_staticsObj[i]->getToReplace())
		{
			auto sprite = m_staticsObj[i]->getSprite();
			int x = (sprite.getPosition().x) / (float)P_SIZE;
			int y = (sprite.getPosition().y) / (float)P_SIZE;
			m_staticsObj.push_back(std::make_unique<Key>((KEY), x, y));
			m_staticsObj[i]->setDelete();
		}
	}
}
//-------------------------------------------------------------
//gril which gift the current gift will be

std::unique_ptr<Gift>  DataBase::grillGiftType(icons, int i, int j)
{
	if (!m_GiftsWithTime)
	{
		int type = rand() % (NUM_OF_GIFT_TYPES / 2);
		switch ((giftType)type)
		{
		case giftType::TAKE_TO_PREV_LEVEL:
			return std::make_unique<TakeToPrevLevelGift>((GIFT), i, j);
		case giftType::MOVE_FAIRIES:
			return std::make_unique<RemoveFairiesGift>((GIFT), i, j);
		}
	}
	else
	{
		int type = rand() % (NUM_OF_GIFT_TYPES - 1) + 1;

		switch ((giftType)type)
		{
		case giftType::TAKE_TIME:
			return std::make_unique<TakeTimeGift>((GIFT), i, j);
		case giftType::ADD_TIME:
			return std::make_unique<AddTimeGift>((GIFT), i, j);
		case giftType::MOVE_FAIRIES:
			return std::make_unique<RemoveFairiesGift>((GIFT), i, j);
		}
	}
	return nullptr;
}
//---------------------------------------------
//handle taking gift by the player

void DataBase::takeGift()
{
	resetTakeGifts();

	for (int i = 0; i < m_staticsObj.size(); i++)
	{
		if (typeid(*m_staticsObj[i]) == typeid(RemoveFairiesGift) && m_staticsObj[i]->getToDelete())
			this->eraseAllFairies();

		else if (typeid(*m_staticsObj[i]) == typeid(TakeTimeGift) && m_staticsObj[i]->getToDelete())
			m_takeGifts[TAKE_TIME] = true;

		else if (typeid(*m_staticsObj[i]) == typeid(TakeToPrevLevelGift) && m_staticsObj[i]->getToDelete())
			m_takeGifts[TAKE_TO_PREV_LEVEL] = true;

		else if (typeid(*m_staticsObj[i]) == typeid(AddTimeGift) && m_staticsObj[i]->getToDelete())
			m_takeGifts[ADD_TIME] = true;
	}
}
//---------------------------------------------
//check if the player win the level means the 
//king reached the throne

bool DataBase::winLevel()
{
	Player* p = m_players[KING].get();
	King* k = dynamic_cast<King*>(p);

	if (k)
		if (k->ReachedTheThrone())
		{
			k->resetReachedTheThrone();
			return true;
		}

	return false;
}
//-----------------------------------------------
//erase all the object from the vectors

void DataBase::eraseObj()
{
	while (!m_staticsObj.empty())
	{
		auto staticPtr = m_staticsObj.begin();
		m_staticsObj.erase(staticPtr);
	}

	while (!m_teleport.empty())
	{
		auto teleportPtr = m_teleport.begin();
		m_teleport.erase(teleportPtr);
	}
	this->eraseAllFairies();
}
//----------------------------------------------
//erase all the fairies from the vectors

void DataBase::eraseAllFairies()
{
	while (!m_fairies.empty())
	{
		auto fairyPtr = m_fairies.begin();
		m_fairies.erase(fairyPtr);
	}
}
//----------------------------------------------

void DataBase::resetTakeGifts()
{
	for (int i = 0; i < NUM_OF_GIFT_TYPES; i++)
		m_takeGifts[i] = false;
}