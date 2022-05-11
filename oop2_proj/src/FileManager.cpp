#pragma once
#include "FileManager.h"
#include <iostream>

//--------------------------------------------------
//constructor

FileManager::FileManager()
{
	//loads from all the files:
	loadDecoration();
	loadAudio();
	loadMusicIcon();
	loadStopAndPlayIcon();
	loadBackgrounds();
	loadResetIcon();
}
//--------------------------------------------------
//return unic pointer to the object
FileManager& FileManager::p2FileManager()
{
	static FileManager m_instance;
	return m_instance;
}
//--------------------------------------------------
// load all the object images

void FileManager::loadDecoration()
{
	SharedDec[LIFE].loadFromFile("life.png");
	SharedDec[DIAMOND].loadFromFile("diamond.png");
	SharedDec[POWER].loadFromFile("power.png");

	//m_dec1

	this->m_font.loadFromFile("Seagram tfb.ttf");
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

const sf::Texture* FileManager::getIconTexture(icons place)const
{
	return &this->m_icons[place];
}
//--------------------------------------------------

const sf::Font* FileManager::getFont()const
{
	return &this->m_font;
}

const sf::Texture* FileManager::getLev1Dec(icons place, levels currLevel) const
{
	switch (currLevel)
	{
	case LEVEL1:
		return &this->m_dec1[place];
		break;
	case LEVEL2:
		return &this->m_dec2[place];
		break;
	case LEVEL3:
		return &this->m_dec3[place];
		break;
	default:
		break;
	}
	
}

