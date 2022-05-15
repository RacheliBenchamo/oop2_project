#pragma once
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

FileManager::FileManager()
{
	//loads from all the files:
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
// //--------------------------------------------------
// load all the object images

void FileManager::loadMovingObj()
{
	m_player.loadFromFile("Player.png");
	//m_monstersIcon[LEVEL1][MONSTER1].loadFromFile("Teleport.png");


}
//--------------------------------------------------
// load all the object images

void FileManager::loadStaticObj()
{
	m_sharedStaticIcon[TELEPORT].loadFromFile("Teleport.png");
	m_sharedStaticIcon[DIAMOND].loadFromFile("Diamond.png");

	m_sharedStaticIcon[LIFE].loadFromFile("life.png");
	//m_sharedStaticIcon[DIAMOND].loadFromFile("Diamond.png");
	m_sharedStaticIcon[POWER].loadFromFile("power.png");

	//m_dec[LEV1][FLOOR].loadFromFile("forestFloor.png");
	//m_dec[LEV2][FLOOR].loadFromFile("desertFloor.png");
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
	m_backgrounds[LEVEL2_BACKGROUND].loadFromFile("gameBackground.png");
	m_backgrounds[LEVEL3_BACKGROUND].loadFromFile("gameBackground.png");
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

const sf::Texture* FileManager::getCurrLevDec(icons icon, levels currLevel) const
{
	return &this->m_dec[currLevel - 1][icon];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getStaticData(icons object)
{
	return m_staticData[object];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getPlayerData()
{
	return m_playerData;
}

//------------------------------------------------------------------------
// Set all animation data used in the game.

void FileManager::setAnimationsData()
{

	m_staticData[TELEPORT]=createStaticAnimationData({ 444, 95 }, { 518,0 }, 6);
	m_staticData[DIAMOND] = createStaticAnimationData({ 900, 110 }, { 49,0 }, 7);
	m_staticData[DIAMOND].m_time[Stay] = 0.2f;

	m_playerData = createPlayerAnimeData();

	/*
	m_staticData[KEY_DATA] =createStaticAnimationData({ 18,39 }, { 0,287 }, { 2,0 }, 4);
	m_staticData[KEY_DATA].m_time[Stay] = 0.2f;

	m_staticData[EXTRA_LIFE_DATA] = createLifeAnimationData();
	m_staticData[EXTRA_LIFE_DATA].m_time[Stay] = 0.5f;


	m_movingObjData[BEAR_DATA] = createMonstersAnimeData();???
	*/
}

//--------------------------------------------------------------------
//Set the Static objects animations data and time.

AnimationData FileManager::createStaticAnimationData(const sf::Vector2i size,
	const sf::Vector2i startPoint, const int count)
{
	auto staticData = AnimationData{};
	sf::Vector2i currSize;

	currSize.x = size.x / count;
	currSize.y = size.y;
	auto currentStart = startPoint;

	auto nextStart = [&]()
	{
		currentStart.x += currSize.x;
		return currentStart;
	};

	staticData.m_data[Stay].emplace_back(currentStart, currSize);

	for (int i = 1; i < count; i++)
	{
		staticData.m_data[Stay].emplace_back(nextStart(), currSize);
	}

	staticData.m_time[Stay] = 0.1f;
	staticData.playOnce[Stay] = false;

	return staticData;
}
//--------------------------- playerAnime ----------------------------
//Set the player animations.

AnimationData FileManager::createPlayerAnimeData()
{
	auto player = AnimationData{};

	setCurrentData(player, Stay, movableAnimationSet
	({ 110, 115 }, { 730, 5 }, 1,Stay), 0.1f, false);

	setCurrentData(player, Right, movableAnimationSet
	({ 230, 115 }, { 480, 5 }, 2, Right), 0.1f, true);

	setCurrentData(player, Jump, movableAnimationSet
	({ 100, 110 }, { 373, 5 }, 1,Jump), 0.15f, true);

	setCurrentData(player, Hit, movableAnimationSet
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

	return player;
}

//-------------------------- setCurrentData --------------------------
//				Set animation the data,time and frequancy.
//--------------------------------------------------------------------
void FileManager::setCurrentData(AnimationData& data, Operation op,
	std::vector<sf::IntRect> inRect, float time, bool once)
{
	data.m_data[op] = inRect;
	data.m_time[op] = time;
	data.playOnce[op] = once;
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
