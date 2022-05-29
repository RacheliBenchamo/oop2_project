#include "DataBase.h"
#include <chrono>
#include <thread>
#include <Windows.h>

using std::this_thread::sleep_for;
using std::cout;

//--------------------------------------------------
//constructor

DataBase::DataBase()
	: m_currTeleport(0), m_currLevel(1)
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
	sf::Vector2f pos(i, j);
	//std::cout <<c <<" " <<pos.x << " " << pos.y << "\n";
		if(!createStaticObj(c, pos))
		createMovingObj(c, pos);
}
//-----------------------------------------------------------
//create all the moving object in the level

void DataBase::createMovingObj(const char c, const sf::Vector2f& pos)
{
	switch (c)
	{
	case PLAYER_C:
		m_player = std::make_unique<Player>(pos+sf::Vector2f(0,20));
		break;
	case  MONSTER1_C:
		m_monsters.push_back(std::make_unique<Monster>(pos + sf::Vector2f(0, 22), levels(m_currLevel),
			MONSTER1, sf::Vector2f(BLOCK_SIZE/1.2 , BLOCK_SIZE/1.2 )));
		break;
	case  MONSTER2_C:
		m_monsters.push_back(std::make_unique<Monster>(pos + sf::Vector2f(0, 22), levels(m_currLevel),
			MONSTER2, sf::Vector2f(BLOCK_SIZE , BLOCK_SIZE)));
		break;
	case  MONSTER3_C:
		m_monsters.push_back(std::make_unique<Monster>(pos + sf::Vector2f(0, 22), levels(m_currLevel),
			MONSTER3, sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)));
		break;
	}
}
//-----------------------------------------------
//create all the static object in the level

bool DataBase::createStaticObj(const char c, const sf::Vector2f &pos)
{
	switch (c)
	{
	//case GATE_C:
	//	m_staticsObj.push_back(std::make_unique<Gate>((GATE), i, j));
	//	return true;
	//	break;
	case TELEPORT_C:
		m_teleport.push_back(std::make_unique<Teleport>( pos));
		return true;
		break;
	case DIAMOND_C:
		m_staticsObj.push_back(std::make_unique<Diamond>(pos));
		return true;
		break;
	case  START_FLOOR_C:
		m_staticsObj.push_back(std::make_unique<Floor>(pos, levels(m_currLevel), 
			L_FLOOR,sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE/1.5)));
		break;
	case  FLOOR_C:
		m_staticsObj.push_back(std::make_unique<Floor>(pos, levels(m_currLevel), M_FLOOR,
			sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 1.5)));
		break;
	case  END_FLOOR_C:
		m_staticsObj.push_back(std::make_unique<Floor>(pos, levels(m_currLevel), R_FLOOR
			,sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 1.5)));
		break;
	case  F_TREE_C:
		m_staticsObj.push_back(std::make_unique<StageDec>(pos, levels(m_currLevel),
			F_TREE,sf::Vector2f(BLOCK_SIZE*1.5, BLOCK_SIZE * 1.5)));
		break;
	case  S_TREE_C:
		m_staticsObj.push_back(std::make_unique<StageDec>(pos, levels(m_currLevel), S_TREE,
			sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE * 1.5)));
		break;
	case  ROCK_C:
		m_staticsObj.push_back(std::make_unique<StageDec>(pos + sf::Vector2f(0, 25), levels(m_currLevel),
			ROCK,sf::Vector2f(BLOCK_SIZE/3, BLOCK_SIZE/3)));
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
	//drowObj<m_staticsObj>();

	drawStaticObj(window);
	drawMovingObj(window);
}
//-----------------------------------------------
//draw all the static object in the level on the window

void DataBase::drawStaticObj(sf::RenderWindow& window)
{
	sf::Time delta_time = m_clock.restart();

	for (auto& e : m_staticsObj)
	{
		e->update(delta_time);
		e->draw(window);
	}
	for (auto& e : m_teleport)
	{
		e->update(delta_time);
		e->draw(window);
	}
}
//---------------------------------------------------
//draw all the moving object in the level on the window

void DataBase::drawMovingObj(sf::RenderWindow& window)

{
	sf::Time delta_time = m_clock.restart();
	for (auto& e : m_monsters)
	{
		e->update(delta_time);
		e->draw(window);
	}
	if (m_player)
	{
		m_player->update(delta_time);
		m_player->draw(window);
	}
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
//handle the moving in this moment

void DataBase::move(sf::Time deltaTime)
{
	handelCollisions();

	//move monsters
	for (auto& f : m_monsters)
	{
		f->setPlayerPos(m_player->getPos());
		f->move(deltaTime, m_levelSize);
	}

	//move current player
	m_player->move(deltaTime,m_levelSize);
	m_player->handleJump(deltaTime, 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space), m_levelSize);
	m_player->handleFall(deltaTime, m_levelSize);
	m_player->setHittingStatus(false);

}
//-------------------------------------------------
//handle the collisions in this moment

void DataBase::handelCollisions()
{
	if(handelPlayerCollisions())
		deleteRelevantObj();
	//handelMonstersCollisions();
	//handelTeleportCollisions();
	
}
//----------------------------------------------------
//handle the current player collisions in this moment

bool DataBase::handelPlayerCollisions()
{
	// check collition with static object
	for (auto& p : m_staticsObj)
		if (m_player->checkCollision(*p))
		{
			processCollision(*m_player, *p);
			return true;
		}
			
	return false;
	

	//for (auto& p : m_players)
	//	if (m_players[m_currPlayer]->checkCollision(*p))
	//		m_players[m_currPlayer]->handleCollision(*p);
}
//----------------------------------------------------
 //handle the fairies collisions in this moment
//
//void DataBase::handelMonstersCollisions()
//{
//	for (auto& f : m_fairies)
//	{
//		for (auto& p : m_players)
//			if (f->checkCollision(*p))
//				f->handleCollision(*p);
//
//		for (auto& c : m_staticsObj)
//			if (f->checkCollision(*c))
//				f->handleCollision(*c);
//
//		for (auto& fa : m_fairies)
//			if (f != fa)
//				if (f->checkCollision(*fa))
//					f->handleCollision(*fa);
//	}
//}
//----------------------------------------------------
//handle the teleports collisions in this moment

void DataBase::handelTeleportCollisions()
{
	/*for (int index = 0; index < m_teleport.size(); index++)
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
	}*/
}
//-----------------------------------------------------
//check if its allowed to enter the teleport

void DataBase::itsAllowedToEnterTheTeleport(int place,int move)
{
	/*if (m_teleport[place + move]->isOpen() && ThereIsNoObjectOnTheMemberTel(place + move))
	{
		m_teleport[place + move]->toClose();
		m_currTeleport = place + move;
		m_players[m_currPlayer]->handleCollision(*m_teleport[place]);
	}*/
}
//-----------------------------------------------------
//check if there is no object on the member teleport

bool DataBase::ThereIsNoObjectOnTheMemberTel(int index)
{
	//for (auto& p : m_players)
	//	if (p->checkCollision(*m_teleport[index]))
			return false;

	//for (auto& fa : m_fairies)
	//	if (fa->checkCollision(*m_teleport[index]))
	//		return false;

	//return true;
}
//-----------------------------------------------------
//delete the relevant Objects from the level

void DataBase::deleteRelevantObj()
{
	//replaceMonsterWithPotion();
	std::erase_if(m_staticsObj, [](const auto& object) {return object->getToDelete(); });
}
//-----------------------------------------------------
//replace the orks that killed with key sprite
//
//void DataBase::replaceMonsterWithPotion()
//{
//	for (int i = 0; i < m_staticsObj.size(); i++)
//	{
//		if (m_staticsObj[i]->getToReplace())
//		{
//			auto sprite = m_staticsObj[i]->getSprite();
//			int x = (sprite.getPosition().x) / (float)P_SIZE;
//			int y = (sprite.getPosition().y) / (float)P_SIZE;
//			m_staticsObj.push_back(std::make_unique<Key>((KEY), x, y));
//			m_staticsObj[i]->setDelete();
//		}
//	}
//}
//-------------------------------------------------------------
//gril which gift the current gift will be

std::unique_ptr<Gift>  DataBase::grillGiftType(icons, int i, int j)
{
	//if (!m_GiftsWithTime)

	//	int type = rand() % (NUM_OF_GIFT_TYPES / 2);
	//switch ((giftType)type)
	//{
	//case giftType::LIFE:
	//	return std::make_unique<LifeGift>((GIFT), i, j);
	//case giftType::POWER:
	//	return std::make_unique<PowerGift>((GIFT), i, j);
	//}
	return nullptr;
}
//---------------------------------------------
//handle taking gift by the player

void DataBase::takeGift()
{
	resetTakeGifts();

	//for (int i = 0; i < m_staticsObj.size(); i++)
	//{
	//	if (typeid(*m_staticsObj[i]) == typeid(RemoveFairiesGift) && m_staticsObj[i]->getToDelete())
	//		this->eraseAllFairies();

	//	else if (typeid(*m_staticsObj[i]) == typeid(TakeTimeGift) && m_staticsObj[i]->getToDelete())
	//		m_takeGifts[TAKE_TIME] = true;

	//	else if (typeid(*m_staticsObj[i]) == typeid(TakeToPrevLevelGift) && m_staticsObj[i]->getToDelete())
	//		m_takeGifts[TAKE_TO_PREV_LEVEL] = true;

	//	else if (typeid(*m_staticsObj[i]) == typeid(AddTimeGift) && m_staticsObj[i]->getToDelete())
	//		m_takeGifts[ADD_TIME] = true;
	//}
}
//---------------------------------------------
//check if the player win the level means the 
//king reached the throne

bool DataBase::winLevel()
{

	if (m_player)
		if (m_player->getDiamondsCount()== m_currLevelMaxDiamonds)
			return true;

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
	this->eraseAllMonsters();
}
//----------------------------------------------
//erase all the fairies from the vectors

void DataBase::eraseAllMonsters()
{
	while (!m_monsters.empty())
	{
		auto monsterPtr = m_monsters.begin();
		m_monsters.erase(monsterPtr);
	}
}
//----------------------------------------------

void DataBase::resetTakeGifts()
{
	for (int i = 0; i < NUM_OF_GIFT_TYPES; i++)
		m_takeGifts[i] = false;
}

//template<class T>
//void DataBase::drowObj()
//{
//	sf::Time delta_time = m_clock.restart();
//
//	for (auto& e : T)
//	{
//		update(delta_time);
//		e->draw(window);
//	}
//}
