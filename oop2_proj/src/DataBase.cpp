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
}
//---------------------------------------------------
//set level size

void DataBase::setLevelSize(const int x, const int y)
{
	m_levelSize.x = x;
	m_levelSize.y = y;
}
//---------------------------------------------------
//create all the object in the level

void DataBase::setData(const char c, const int i, const int j)
{
	sf::Vector2f pos(i, j);
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
		m_player = std::make_unique<Player>(pos+sf::Vector2f(7,20)
			,m_gender, m_stageType);
		break;
	case  MONSTER1_C:
		m_monsters.push_back(std::make_unique<Monster>(pos,MONSTER1, 
			sf::Vector2f(BLOCK_SIZE / 1.2, BLOCK_SIZE / 1.2),
			MON1_FORCE, m_stageType));
		break;
	case  MONSTER2_C:
		m_monsters.push_back(std::make_unique<Monster>(pos,MONSTER2,
			sf::Vector2f(BLOCK_SIZE , BLOCK_SIZE), MON2_FORCE,
			m_stageType));
		break;
	case  MONSTER3_C:
		m_monsters.push_back(std::make_unique<Monster>(pos ,MONSTER3, 
			sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE), MON3_FORCE,
			m_stageType));
		break;
	}
}
//---------------------------------------------------
//create all the static object in the level

bool DataBase::createStaticObj(const char c, const sf::Vector2f &pos)
{
	switch (c)
	{
	case GATE_C:
		setStaticObject<Gate>(pos + sf::Vector2f(0, 5));
		return true;
	case TELEPORT_C:
		m_teleport.push_back(std::make_unique<Teleport>( pos+ HEIGHT));
		return true;
	case DIAMOND_C:
		m_currLevelMaxDiamonds++;
		setStaticObject<Diamond>(pos);
		return true;
	case  ROPE_C:
		m_rope.push_back(std::make_unique<Rope>(pos + sf::Vector2f(0, -27)));
		return true;
	case  START_FLOOR_C:
		setStaticObject<LeftFloor>(pos, levels(m_stageType),
			L_FLOOR, sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 1.5), FLOOR_ROCK);
		return true;
	case  FLOOR_C:
		setStaticObject<Floor>(pos, levels(m_stageType), M_FLOOR,
			sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 1.5), FLOOR_ROCK);
		return true;
	case  END_FLOOR_C:
		setStaticObject<RightFloor>(pos, levels(m_stageType), R_FLOOR
			, sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 1.5), FLOOR_ROCK);
		return true;
	case  F_TREE_C:
		setStaticObject<StageDec>(pos, levels(m_stageType),
			F_TREE, sf::Vector2f(BLOCK_SIZE * 1.5, BLOCK_SIZE * 1.5), TREE);
		return true;
	case  S_TREE_C:
		setStaticObject<StageDec>(pos, levels(m_stageType), S_TREE,
			sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE * 1.5), TREE);
		return true;
	case  ROCK_C:
		setStaticObject<StageDec>(pos + sf::Vector2f(0, 25), levels(m_stageType),
			ROCK, sf::Vector2f(BLOCK_SIZE / 3, BLOCK_SIZE / 3), FLOOR_ROCK);
		return true;
	default:
		return false;
	}
}
//---------------------------------------------------
//draw all the object in the level on the window

void DataBase::draw(sf::RenderWindow& window,const bool playButton)
{
	drawStaticObj(window, playButton);
	drawMovingObj(window, playButton);
}
//---------------------------------------------------
//draw all the static object in the level on the window

void DataBase::drawStaticObj(sf::RenderWindow& window, const bool playButton)
{
	sf::Time deltaTime = m_clock.restart();

	for (auto& e : m_staticsObj)
	{
		if(playButton)
			e->update(deltaTime);
		e->draw(window);
	}
	for (auto& e : m_teleport)
	{
		e->update(deltaTime);
		e->draw(window);
	}
	for (auto& e : m_rope)
	{
		e->draw(window);
	}
}
//---------------------------------------------------
//draw all the moving object in the level on the window

void DataBase::drawMovingObj(sf::RenderWindow& window, const bool playButton)
{
	sf::Time delta_time = m_clock.restart();

	for (auto& m : m_monsters)
	{
		if(playButton)
			m->update(delta_time);
		m->draw(window);
		if (m->toPrintDamage())
		{
			m->printDamage(window);
			m->setHurt(false);
		}
	}
	if(m_player)
	{
		m_player->update(delta_time);
		m_player->draw(window);
		if (m_player->toPrintDamage())
		{
			m_player->printDamage(window);
			m_player->setHurt(false);
		}
	}
}
//---------------------------------------------------
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
//---------------------------------------------------
//handle the moving in this moment

void DataBase::move(const sf::Time deltaTime)
{
	//move monsters
	for (auto& f : m_monsters)
	{
		f->setPlayerPos(m_player->getPos());
		f->move(deltaTime, m_levelSize);
	}
	//move current player
	if(m_player)
	m_player->move(deltaTime,m_levelSize);

	handelCollisions();
	handelPlayerStuff(deltaTime);
}
//---------------------------------------------------
//handle the collisions in this moment

void DataBase::handelCollisions()
{
	handelMovingCollisions();
	handelTeleportCollisions();	
	deleteRelevantObj();
}
//---------------------------------------------------
//handle the current player collisions in this moment

void DataBase::handelMovingCollisions()
{
	for (auto& r : m_rope)
		if (m_player->checkCollision(*r))
			processCollision(*m_player, *r);

	for (auto& s : m_staticsObj)
	{
		if (m_player->checkCollision(*s))
			processCollision(*m_player, *s);
		for (auto& m : m_monsters)
		{
			if (m->checkCollision(*s))
				processCollision(*m, *s);
		}
		if (typeid(*s) == typeid(Gate)
			&& m_player->getDiamondsCount() == m_currLevelMaxDiamonds)
			static_cast<Gate&>(*s).open();
	}
	for (auto& m : m_monsters)
	{
		if (m_player->checkCollision(*m))
			processCollision(*m_player, *m);
	}
}
//---------------------------------------------------
//handle the teleports collisions in this moment

void DataBase::handelTeleportCollisions()
{
	for (int index = 0; index < m_teleport.size(); index++)
	{
		if (!(m_player->checkCollision(*m_teleport[m_currTeleport])))
			m_teleport[m_currTeleport]->toOpen();

		if (m_player->checkCollision(*m_teleport[index])
			&& m_teleport[index]->isOpen())
		{
			if (index % 2 == 0)
				AllowedToEnterTeleport(index , 1);
			else
				AllowedToEnterTeleport(index , -1);
		}
	}
}
//---------------------------------------------------

void DataBase::handelPlayerStuff(const sf::Time deltaTime)
{
	m_player->setHittingStatus(false);
	m_player->handleJump(deltaTime,sf::Keyboard::isKeyPressed(sf::Keyboard::Space), m_levelSize);
	m_player->handleFall(deltaTime, m_levelSize);
	m_player->setHittingStatus(false);
	m_player->handleClimbing();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		m_player->hit();

}
//---------------------------------------------------
//check if its allowed to enter the teleport

void DataBase::AllowedToEnterTeleport(const int place, const int move)
{
	if (m_teleport[place + move]->isOpen() && 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_teleport[place + move]->toClose();
		m_currTeleport = place + move;
		processCollision(*m_player, *m_teleport[place]);
	}
}
//---------------------------------------------------
//delete the relevant Objects from the level

void DataBase::deleteRelevantObj()
{
	replaceMonsterWithPotion();
	std::erase_if(m_staticsObj, [](const auto& object) 
		{return object->getToDelete(); });
}
//---------------------------------------------------
//replace the orks that killed with key sprite

void DataBase::replaceMonsterWithPotion()
{
	for (int i=0 ; i < m_monsters.size() ;i++)
	{
		if (m_monsters[i]->getToDelete())
		{
			randPotion(m_monsters[i]->getPos());
			m_monsters.erase(m_monsters.begin()+i);
		}
	}
}
//---------------------------------------------------
//gril curent poision  

void  DataBase::randPotion(const sf::Vector2f pos)
{
	int type = rand() %4;
	switch ((posion)type)
	{
	case posion::POWERPOSION:
		m_staticsObj.push_back(std::make_unique<PowerPotion>(pos));
		break;
	case posion::LIFE_POSION:
	case 2:
		m_staticsObj.push_back(std::make_unique<LifePotion>(pos));
		break;
	default:
		break;
	}
}
//---------------------------------------------------
//check if the player win the level means the 
//player reached the gate

bool DataBase::winLevel()const
{
	if (m_player)
		if (m_player->getGotToNextLev())
			return true; 
	return false;
}
//---------------------------------------------------
//erase all the object from the vectors

void DataBase::eraseObj()
{
	while (!m_staticsObj.empty())
	{
		auto staticPtr = m_staticsObj.begin();
		m_staticsObj.erase(staticPtr);
	}
	while (!m_rope.empty())
	{
		auto ropePtr = m_rope.begin();
		m_rope.erase(ropePtr);
	}
	while (!m_teleport.empty())
	{
		auto teleportPtr = m_teleport.begin();
		m_teleport.erase(teleportPtr);
	}
	eraseAllMonsters();
}
//---------------------------------------------------
//erase all the monsters

void DataBase::eraseAllMonsters()
{
	while (!m_monsters.empty())
	{
		auto monsterPtr = m_monsters.begin();
		m_monsters.erase(monsterPtr);
	}
}