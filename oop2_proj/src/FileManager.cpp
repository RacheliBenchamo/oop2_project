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
	//m_player.loadFromFile("Player.png");
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

	//m_dec[LEV1][FLOOR]....

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

sf::Texture* FileManager::getMonstersTexture(const icons place, levels currLevel)
{
	return &this->m_monstersIcon[currLevel - 1][place];
}
//------------------------------------------------------------------

const sf::Texture* FileManager::getCurrLevDec(icons place, levels currLevel) const
{
	return &this->m_dec[currLevel - 1][place];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getStaticData(icons object)
{
	return m_staticData[object];
}
//--------------------------------------------------------------------
//Set the Static objects animations data and time.

AnimationData FileManager::createStaticAnimationData(const sf::Vector2i size,const sf::Vector2i initSpace,
	const sf::Vector2i middleSpace,const int count)
{
	auto staticData = AnimationData{};
	auto currentStart = initSpace;
	auto nextStart = [&]()
	{
		currentStart.x += size.x;
		currentStart += middleSpace;
		return currentStart;
	};

	staticData.m_data[Stay].emplace_back(currentStart, size);

	for (int i = 0; i < count; i++) 
	{
		staticData.m_data[Stay].emplace_back(nextStart(), size);
	}

	staticData.m_time[Stay] = 0.1f;
	staticData.playOnce[Stay] = false;

	return staticData;
}

//------------------------------------------------------------------------
// Set all animation data used in the game.

void FileManager::setAnimationsData()
{

	m_staticData[TELEPORT]=createStaticAnimationData({ 74, 100 }, { 518,0 }, { 0,0 }, 6);
	m_staticData[DIAMOND] = createStaticAnimationData({ 100, 100 }, { 43,0 }, { 0,0 }, 6);

	/*
	m_staticData[KEY_DATA] =createStaticAnimationData({ 18,39 }, { 0,287 }, { 2,0 }, 4);
	m_staticData[KEY_DATA].m_time[Stay] = 0.2f;

	m_staticData[EXTRA_LIFE_DATA] = createLifeAnimationData();
	m_staticData[EXTRA_LIFE_DATA].m_time[Stay] = 0.5f;

	m_movingObjData[PLAYER_DATA] = createPlayerAnimeData();

	m_movingObjData[BEAR_DATA] = createMonstersAnimeData();???
	*/
}

