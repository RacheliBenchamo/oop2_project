#pragma once
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

FileManager::FileManager()
{
	//loads from all the files:
	loadBackgroundIcons();
	loadMovingObj();
	loadStaticObj();
	loadAudio();
	loadMusicIcon();
	loadStopAndPlayIcon();
	loadBackgrounds();
	loadResetIcon();
	setAnimationsData();
	this->m_font.loadFromFile("Seagram tfb.ttf");

}
//--------------------------------------------------
//return unic pointer to the object
FileManager& FileManager::p2FileManager()
{
	static FileManager m_instance;
	return m_instance;
}
//----------------------------------------------------
void FileManager::loadBackgroundIcons()
{
	m_backgroundIcons[B_POWER].loadFromFile("PowerIcon.png");
	m_backgroundIcons[B_LIFE].loadFromFile("LifeIcon.png");
	m_backgroundIcons[B_DIAMOND].loadFromFile("DiamondIcon.png");
	//m_backgroundIcons[B_RESTART].loadFromFile("resetButton.png");
}

// //--------------------------------------------------
// load all the object images

void FileManager::loadMovingObj()
{
	m_player.loadFromFile("Player.png");

	m_monstersIcon[LEVEL1][MONSTER1].loadFromFile("ForMonster1.png");
	m_monstersIcon[LEVEL1][MONSTER2].loadFromFile("ForMonster2.png");
	m_monstersIcon[LEVEL1][MONSTER3].loadFromFile("ForMonster3.png");

	m_monstersIcon[LEVEL2][MONSTER1].loadFromFile("SnoMonster1.png");
	m_monstersIcon[LEVEL2][MONSTER2].loadFromFile("SnoMonster2.png");
	m_monstersIcon[LEVEL2][MONSTER3].loadFromFile("SnoMonster3.png");

	m_monstersIcon[LEVEL3][MONSTER1].loadFromFile("DesMonster1.png");
	m_monstersIcon[LEVEL3][MONSTER2].loadFromFile("DesMonster2.png");
	m_monstersIcon[LEVEL3][MONSTER3].loadFromFile("DesMonster3.png");
}
//--------------------------------------------------
// load all the object images

void FileManager::loadStaticObj()
{
	m_sharedStaticIcon[TELEPORT].loadFromFile("Teleport.png");
	m_sharedStaticIcon[DIAMOND].loadFromFile("Diamond.png");
	m_dec.loadFromFile("staticDec.png");

	loadStaticObjRect();
}

//--------------------------------------------------
// load all the rect of the static decoration un the game
void FileManager::loadStaticObjRect()
{
	m_decRect[LEVEL1][L_FLOOR] = LEFT_FLOOR_L1;
	m_decRect[LEVEL1][M_FLOOR] = MIDDLE_FLOOR_L1;
	m_decRect[LEVEL1][R_FLOOR] = RIGHT_FLOOR_L1;
	m_decRect[LEVEL1][F_TREE] = FIRST_TREE_L1;
	m_decRect[LEVEL1][S_TREE] = SECOUND_TREE_L1;
	m_decRect[LEVEL1][ROCK] = ROCK_L1;

	m_decRect[LEVEL2][L_FLOOR] = LEFT_FLOOR_L2;
	m_decRect[LEVEL2][M_FLOOR] = MIDDLE_FLOOR_L2;
	m_decRect[LEVEL2][R_FLOOR] = RIGHT_FLOOR_L2;
	m_decRect[LEVEL2][F_TREE] = FIRST_TREE_L2;
	m_decRect[LEVEL2][S_TREE] = SECOUND_TREE_L2;
	m_decRect[LEVEL2][ROCK] = ROCK_L2;

	m_decRect[LEVEL3][L_FLOOR] = LEFT_FLOOR_L3;
	m_decRect[LEVEL3][M_FLOOR] = MIDDLE_FLOOR_L3;
	m_decRect[LEVEL3][R_FLOOR] = RIGHT_FLOOR_L3;
	m_decRect[LEVEL3][F_TREE] = FIRST_TREE_L3;
	m_decRect[LEVEL3][S_TREE] = SECOUND_TREE_L3;
	m_decRect[LEVEL3][ROCK] = ROCK_L3;

}
//--------------------------------------------------
// load all the audio

void FileManager::loadAudio()
{
	m_audio[S_TOUCH_WALL].loadFromFile("touchWallSound.wav");
	m_audio[S_TURN_OFF_FIRE].loadFromFile("turnOffFireSound.wav");
	m_audio[S_GIFT].loadFromFile("giftSound.wav");
	m_audio[S_KILL_ORK].loadFromFile("killOrkSound.wav");
	m_audio[S_IN_TELEPORT].loadFromFile("inTeleportSound.wav");
	m_audio[S_WIN_LEVEL].loadFromFile("winLevelSound.wav");
	m_audio[S_WIN_GAME].loadFromFile("winGameSound.wav");
	m_audio[S_BACKROUND].loadFromFile("backgroundMusic.wav");
	m_audio[S_TOUCH_FIRE].loadFromFile("touchFireSound.wav");
	m_audio[S_TOUCH_ORK].loadFromFile("touchOrkSound.wav");
	m_audio[S_TOUCH_GATE].loadFromFile("touchGateSound.wav");
	m_audio[S_TAKE_KEY].loadFromFile("takeKeySound.wav");
	m_audio[S_OPEN_GATE].loadFromFile("openGateSound.wav");
	m_audio[S_TOUCH_FAIRY].loadFromFile("touchFairySound.wav");

}
//--------------------------------------------------
// load the music sprites

void FileManager::loadMusicIcon()
{
	m_musicTexture[0].loadFromFile("musicOn.png");
	m_musicTexture[1].loadFromFile("musicOff.png");
}
//--------------------------------------------------
// load the stop and play sprites

void FileManager::loadStopAndPlayIcon()
{
	m_playStopTexture[0].loadFromFile("playButton.png");
	m_playStopTexture[1].loadFromFile("stopButton.png");
}
//--------------------------------------------------
// load the restart sprite

void FileManager::loadResetIcon()
{
	m_restartIcon.loadFromFile("resetButton.png");
}
//--------------------------------------------------
// load the backgrounds sprites

void FileManager::loadBackgrounds()
{
	m_backgrounds[MENU_BACKGROUND].loadFromFile("menuBackground.png");
	m_backgrounds[LEVEL1_BACKGROUND].loadFromFile("gameBackground.png");
	m_backgrounds[LEVEL2_BACKGROUND].loadFromFile("snowBackground.png");
	m_backgrounds[LEVEL3_BACKGROUND].loadFromFile("desertBackground.png");
	m_backgrounds[HELP_BACKGROUND].loadFromFile("helpBackground.png");
	m_backgrounds[WIN_LEVEL_BACKGROUND].loadFromFile("winLevelBackground.png");
	m_backgrounds[WIN_GAME_BACKGROUND].loadFromFile("winGameBackground.png");
}
//--------------------------------------------

const sf::SoundBuffer* FileManager::getSound(sounds sound)const
{
	return &this->m_audio[(int)sound];
}
//--------------------------------------------------

const sf::Texture* FileManager::getMusicIcon(bool musicOn)const
{
	if (musicOn)
		return &this->m_musicTexture[0];
	else
		return &this->m_musicTexture[1];
}
//--------------------------------------------------

const sf::Texture* FileManager::getPlayAndStopIcon(bool toPlay)const
{
	if (toPlay)
		return &this->m_playStopTexture[1];
	else
		return &this->m_playStopTexture[0];
}
const sf::Texture* FileManager::getBIcons(bIcons place)const
{
	return &this->m_backgroundIcons[place];
}
//--------------------------------------------------

const sf::Texture* FileManager::getRestartIcon()const
{
		return &this->m_restartIcon;
}
//--------------------------------------------------

const sf::Texture* FileManager::getBackGround(backgroundsType place)const
{
	return &this->m_backgrounds[place];
}
//--------------------------------------------------

const sf::Font* FileManager::getFont()const
{
	return &this->m_font;
}
//--------------------------------------------------

sf::Texture* FileManager::getSharedStaticTexture(const icons place)
{
	return &this->m_sharedStaticIcon[place];
}
//--------------------------------------------------

sf::Texture* FileManager::getMonstersTexture(const icons place, const levels currLevel)
{
	return &this->m_monstersIcon[currLevel - 1][place];
}
//--------------------------------------------------

sf::Texture* FileManager::getPlayerTexture()
{
	return &this->m_player;
}
//------------------------------------------------------------------
const sf::Texture* FileManager::getDec() const
{
	return &this->m_dec;
}
//------------------------------------------------------------------

//get the decoration of the level
const sf::IntRect FileManager::getCurrLevDecRect(levels currLevel, decoration dec) const
{
	return this->m_decRect[currLevel - 1][dec];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getStaticData(icons object)
{
	return m_staticData[object];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getMonstersData(levels lev,icons object)
{
	return m_monsterData[lev-1][object];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getPlayerData()
{
	return m_playerData;
}
//----------------------- movableAnimationSet ------------------------
//		Set the Movable objects animations data, time and frequancy.

std::vector<sf::IntRect> FileManager::movableAnimationSet(
	const sf::Vector2i size,
	const sf::Vector2i startPos,
	const int count, Operation typeOperation)
{
	auto stand_anime = AnimationData{};
	auto currentStart = startPos;
	sf::Vector2i currSize;

	currSize.x = size.x / count;
	currSize.y = size.y;

	auto nextStart = [&]()
	{
		currentStart.x += currSize.x;
		return currentStart;
	};

	stand_anime.m_data[typeOperation].emplace_back(currentStart, currSize);

	for (int i = 1; i < count; i++)
	{
		stand_anime.m_data[typeOperation].emplace_back(nextStart(), currSize);
	}

	return stand_anime.m_data[typeOperation];
}
//-------------------------- setCurrentData --------------------------
//				Set animation the data,time and frequancy.

void FileManager::setCurrentData(AnimationData& data, Operation op,
	std::vector<sf::IntRect> inRect, float time, bool once)
{
	data.m_data[op] = inRect;
	data.m_time[op] = time;
	data.playOnce[op] = once;
}
//------------------------------------------------------------------------
// Set all animation data used in the game.

void FileManager::setAnimationsData()
{
	setCurrentData(m_staticData[TELEPORT], Stay, movableAnimationSet
	({ 444, 95 }, { 518,0 }, 6, Stay), 0.1f, false);

	setCurrentData(m_staticData[DIAMOND], Stay, movableAnimationSet
	({ 900, 110 }, { 49,0 }, 7, Stay), 0.2f, false);

	createPlayerAnimeData();
	createForestMonstersAnimeData();
	createSnowMonstersAnimeData();
	createDesertMonstersAnimeData();
}

//--------------------------- playerAnime ----------------------------
//Set the player animations.

void FileManager::createPlayerAnimeData()
{
	setCurrentData(m_playerData, Stay, movableAnimationSet
	({ 110, 115 }, { 730, 5 }, 1,Stay), 0.2f, false);

	setCurrentData(m_playerData, Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);

	setCurrentData(m_playerData, Jump, movableAnimationSet
	({ 100, 110 }, { 373, 5 }, 1,Jump), 0.15f, true);

	setCurrentData(m_playerData, Hit, movableAnimationSet
	({ 220, 115 }, { 133, 5 }, 2, Hit), 0.05f, true);

	//setCurrentData(player, Operation::Rope, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Rope), 0.05f, true);
	// 
	//setCurrentData(player, Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(player, Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	//return player;
}
//--------------------------- monstersAnime ----------------------------
//Set the monsters animations.

void FileManager::createForestMonstersAnimeData()
{

	setCurrentData(m_monsterData[LEVEL1][MONSTER1], Stay, movableAnimationSet
	({ 178, 55 }, { 1, 1 }, 3, Stay), 0.01f, false);

	/*setCurrentData(m_monsterData[LEVEL1][MONSTER1], Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);*/

	// 
	//setCurrentData(m_monsterData[LEVEL1][MONSTER1], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL1][MONSTER1], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL1][MONSTER2], Stay, movableAnimationSet
	({ 355, 90 }, { 1, 1 }, 4, Stay), 0.01f, false);

	/*setCurrentData(m_monsterData[LEVEL1][MONSTER2], Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);*/

	// 
	//setCurrentData(m_monsterData[LEVEL1][MONSTER2], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL1][MONSTER2], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Stay, movableAnimationSet
	({ 297, 65 }, { 9, 6 }, 3, Stay), 0.02f, false);

	/*
	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);*/

	// 
	//setCurrentData(m_monsterData[LEVEL1][MONSTER3], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL1][MONSTER3], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);
}
//----------------------------------------------------

void FileManager::createSnowMonstersAnimeData()
{
	setCurrentData(m_monsterData[LEVEL2][MONSTER1], Stay, movableAnimationSet
	({ 225, 35 }, { 1, 6 },5, Stay), 0.01f, false);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER1], Walk, movableAnimationSet
	//({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);

	// 
	//setCurrentData(m_monsterData[LEVEL2][MONSTER1], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER1], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL2][MONSTER2], Stay, movableAnimationSet
	({ 610, 65 }, { 13, 36 },4, Stay), 0.02f, false);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER2], Walk, movableAnimationSet
	//({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);

	// 
	//setCurrentData(m_monsterData[LEVEL2][MONSTER2], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER2], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL2][MONSTER3], Stay, movableAnimationSet
	({ 129, 40 }, { 0, 6 }, 3, Stay), 0.02f, false);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER3], Walk, movableAnimationSet
	//({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);

	// 
	//setCurrentData(m_monsterData[LEVEL2][MONSTER3], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL2][MONSTER3], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);
}
//----------------------------------------------------

void FileManager::createDesertMonstersAnimeData()
{
	setCurrentData(m_monsterData[LEVEL3][MONSTER1], Stay, movableAnimationSet
	({ 416, 76 }, { 1, 4 }, 6, Stay), 0.02f, false);

	/*setCurrentData(m_monsterData[LEVEL3][MONSTER1], Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);*/

	// 
	//setCurrentData(m_monsterData[LEVEL3][MONSTER1], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL3][MONSTER1], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL3][MONSTER2], Stay, movableAnimationSet
	({ 526, 95 }, { 1, 0 },9, Stay), 0.01f, false);

	//setCurrentData(m_monsterData[LEVEL3][MONSTER2], Walk, movableAnimationSet
	//({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);

	// 
	//setCurrentData(m_monsterData[LEVEL3][MONSTER2], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL3][MONSTER2], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);

	setCurrentData(m_monsterData[LEVEL3][MONSTER3], Stay, movableAnimationSet
	({ 666, 42 }, { 8, 9 }, 11, Stay), 0.01f, false);

	/*setCurrentData(m_monsterData[LEVEL3][MONSTER3], Walk, movableAnimationSet
	({ 240, 115 }, { 480, 5 }, 2, Walk), 0.01f, false);*/

	// 
	//setCurrentData(m_monsterData[LEVEL3][MONSTER3], Operation::Hurt, movableAnimationSet
	//({ 37, 36 }, { 0, 405 }, { 0, 0 }, 8,
	//	Operation::Hurt), 0.05f, true);

	//setCurrentData(m_monsterData[LEVEL3][MONSTER3], Operation::Dead, movableAnimationSet
	//({ 50, 30 }, { 0, 443 }, { 0, 0 }, 5,
	//	Operation::Dead), 0.15f, true);
}

