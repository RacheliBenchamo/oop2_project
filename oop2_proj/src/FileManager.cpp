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
	this->m_font.loadFromFile("Tinos-BoldItalic.ttf");

}
//--------------------------------------------------
//return unic pointer to the object
FileManager& FileManager::instance()
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
}

// //--------------------------------------------------
// load all the object images

void FileManager::loadMovingObj()
{
	m_player.loadFromFile("Player.png");
	loadPlayerRect();

	m_monstersIcon[FOREST][MONSTER1].loadFromFile("ForMonster1.png");
	m_monstersIcon[FOREST][MONSTER2].loadFromFile("ForMonster2.png");
	m_monstersIcon[FOREST][MONSTER3].loadFromFile("ForMonster3.png");

	m_monstersIcon[SNOW][MONSTER1].loadFromFile("SnoMonster1.png");
	m_monstersIcon[SNOW][MONSTER2].loadFromFile("SnoMonster2.png");
	m_monstersIcon[SNOW][MONSTER3].loadFromFile("SnoMonster3.png");

	m_monstersIcon[DESERT][MONSTER1].loadFromFile("DesMonster1.png");
	m_monstersIcon[DESERT][MONSTER2].loadFromFile("DesMonster2.png");
	m_monstersIcon[DESERT][MONSTER3].loadFromFile("DesMonster3.png");
}
//--------------------------------------------------
// load all the object images

void FileManager::loadStaticObj()
{
	m_sharedStaticIcon[TELEPORT].loadFromFile("Teleport.png");
	m_sharedStaticIcon[DIAMOND].loadFromFile("Diamond.png");
	m_sharedStaticIcon[POTION_L].loadFromFile("LifePotion.png");
	m_sharedStaticIcon[POTION_P].loadFromFile("PowerPotion.png");
	m_sharedStaticIcon[ROPE].loadFromFile("Rope.png");
	m_sharedStaticIcon[GATE].loadFromFile("Gate.png");

	m_dec[0].loadFromFile("staticDec.png");
	m_dec[1].loadFromFile("trees.png");

	loadStaticObjRect();
}

//--------------------------------------------------
// load all the rect of the static decoration un the game
void FileManager::loadStaticObjRect()
{
	m_decRect[FOREST][L_FLOOR] = LEFT_FLOOR_L1;
	m_decRect[FOREST][M_FLOOR] = MIDDLE_FLOOR_L1;
	m_decRect[FOREST][R_FLOOR] = RIGHT_FLOOR_L1;
	m_decRect[FOREST][F_TREE] = FIRST_TREE_L1;
	m_decRect[FOREST][S_TREE] = SECOUND_TREE_L1;
	m_decRect[FOREST][ROCK] = ROCK_L1;

	m_decRect[SNOW][L_FLOOR] = LEFT_FLOOR_L2;
	m_decRect[SNOW][M_FLOOR] = MIDDLE_FLOOR_L2;
	m_decRect[SNOW][R_FLOOR] = RIGHT_FLOOR_L2;
	m_decRect[SNOW][F_TREE] = FIRST_TREE_L2;
	m_decRect[SNOW][S_TREE] = SECOUND_TREE_L2;
	m_decRect[SNOW][ROCK] = ROCK_L2;

	m_decRect[DESERT][L_FLOOR] = LEFT_FLOOR_L3;
	m_decRect[DESERT][M_FLOOR] = MIDDLE_FLOOR_L3;
	m_decRect[DESERT][R_FLOOR] = RIGHT_FLOOR_L3;
	m_decRect[DESERT][F_TREE] = FIRST_TREE_L3;
	m_decRect[DESERT][S_TREE] = SECOUND_TREE_L3;
	m_decRect[DESERT][ROCK] = ROCK_L3;

}
//--------------------------------------------------
// load all the rect of the static decoration un the game
void FileManager::loadPlayerRect()
{
	m_PlayerRect[MALE] = MALE_RECT;
	m_PlayerRect[FEMALE] = FEMALE_RECT;
}
//--------------------------------------------------
// load all the audio

void FileManager::loadAudio()
{
	
	m_audio[S_MENU].loadFromFile("MenuBackground.wav");
	m_audio[S_LOSE_LEVEL].loadFromFile("LoseLevelSound.wav");
	m_audio[S_TAKE_DIAMOND].loadFromFile("pickUpDiamond.wav");
	m_audio[S_IN_TELEPORT].loadFromFile("InTeleportSound.wav");
	m_audio[S_TAKE_KEY].loadFromFile("takeKeySound.wav");
	m_audio[S_WIN_LEVEL].loadFromFile("winLevelSound.wav");
	m_audio[S_WIN_GAME].loadFromFile("winGameSound.wav");
	m_audio[S_TAKE_POSION].loadFromFile("potionDrinking.wav");
	m_audio[S_ABOVE].loadFromFile("button_hover_sound.wav");
	m_audio[S_CLICKED].loadFromFile("button_clicked_sound.wav");

	m_backGroundAudio[FOREST].loadFromFile("Level1backgraund.wav");
	m_backGroundAudio[SNOW].loadFromFile("Level2backgraund.wav");
	m_backGroundAudio[DESERT].loadFromFile("Level3backgraund.wav");

	//for 3 levels
	m_playerAudio[FOREST][WALK].loadFromFile("GrassWalking.wav");
	m_playerAudio[SNOW][WALK].loadFromFile("IceWalking.wav");
	m_playerAudio[DESERT][WALK].loadFromFile("SandWalking.wav");

	//for each monster in each level
	m_monstersAudio[FOREST][HIT][M_FIRST].loadFromFile("MushriHit.wav");
	m_monstersAudio[FOREST][HURT][M_FIRST].loadFromFile("MushriHurt.wav");
	m_monstersAudio[FOREST][HIT][M_SECOND].loadFromFile("TreetHit.wav");
	m_monstersAudio[FOREST][HURT][M_SECOND].loadFromFile("TreetHurt.wav");
	m_monstersAudio[FOREST][HIT][M_THIRD].loadFromFile("GreemonHit.wav");
	m_monstersAudio[FOREST][HURT][M_THIRD].loadFromFile("GreemonHurt.wav");

	m_monstersAudio[SNOW][HIT][M_FIRST].loadFromFile("PenguwulungHit.wav");
	m_monstersAudio[SNOW][HURT][M_FIRST].loadFromFile("PenguwulungHurt.wav");
	m_monstersAudio[SNOW][HIT][M_SECOND].loadFromFile("SnowolfHit.wav");
	m_monstersAudio[SNOW][HURT][M_SECOND].loadFromFile("SnowolfHurt.wav");
	m_monstersAudio[SNOW][HIT][M_THIRD].loadFromFile("YetteyeyHit.wav");
	m_monstersAudio[SNOW][HURT][M_THIRD].loadFromFile("YetteyeyHurt.wav");

	m_monstersAudio[DESERT][HIT][M_FIRST].loadFromFile("CactisHit.wav");
	m_monstersAudio[DESERT][HURT][M_FIRST].loadFromFile("CactisHurt.wav");
	m_monstersAudio[DESERT][HIT][M_SECOND].loadFromFile("SuricatiHit.wav");
	m_monstersAudio[DESERT][HURT][M_SECOND].loadFromFile("SuricatiHurt.wav");
	m_monstersAudio[DESERT][HIT][M_THIRD].loadFromFile("FroggoHit.wav");
	m_monstersAudio[DESERT][HURT][M_THIRD].loadFromFile("FroggoHurt.wav");
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

void FileManager::startSound(sf::SoundBuffer* sound,const int volum)const
{
	static sf::Sound effect;
	effect.setBuffer(*sound);
	effect.setVolume(volum);
	effect.play();
}
	
	
//--------------------------------------------------

void FileManager::startBackgraundSound(sf::SoundBuffer* sound, const int volum)const
{
	static sf::Sound effect;
	effect.setBuffer(*sound);
	effect.play();
	effect.setVolume(volum);
}
//--------------------------------------------------
// load the backgrounds sprites

void FileManager::loadBackgrounds()
{
	m_backgrounds[MENU_BACKGROUND].loadFromFile("menuBackground.png");
	m_backgrounds[FOREST_BACKGROUND].loadFromFile("forestBackground.png");
	m_backgrounds[SNOW_BACKGROUND].loadFromFile("snowBackground.png");
	m_backgrounds[DESERT_BACKGROUND].loadFromFile("desertBackground.png");
	m_backgrounds[HELP_BACKGROUND].loadFromFile("helpBackground.png");
	m_backgrounds[LOSE_LEVEL_BACKGROUND].loadFromFile("LoseGameBackground.png");
	m_backgrounds[WIN_GAME_BACKGROUND].loadFromFile("winGameBackground.png");
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getPlayerSound(const playerSounds sound,
	const levels currLevel)
{
	return &m_playerAudio[currLevel-1][sound];
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getMonsterSound(const monsterSounds sound, 
	const levels currLevel, const icons currMonster)
{
	return &m_monstersAudio[currLevel-1][sound][currMonster];
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getBackgraundSaund(const levels currLevel)
{
	return &this->m_backGroundAudio[currLevel];
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getShareSaund(const sounds sound)
{
	return &this->m_audio[sound];
}
//--------------------------------------------------

const sf::Texture* FileManager::getMusicIcon(const bool musicOn)const
{
	if (musicOn)
		return &this->m_musicTexture[0];
	else
		return &this->m_musicTexture[1];
}
//--------------------------------------------------

const sf::Texture* FileManager::getPlayAndStopIcon(const bool toPlay)const
{
	if (toPlay)
		return &this->m_playStopTexture[1];
	else
		return &this->m_playStopTexture[0];
}
const sf::Texture* FileManager::getBIcons(const bIcons place)const
{
	return &this->m_backgroundIcons[place];
}
//--------------------------------------------------

const sf::Texture* FileManager::getRestartIcon()const
{
		return &this->m_restartIcon;
}
//--------------------------------------------------

const sf::Texture* FileManager::getBackGround(const backgroundsType place)const
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
	return &this->m_monstersIcon[currLevel-1][place];
}
//--------------------------------------------------

sf::Texture* FileManager::getPlayerTexture()
{
	return &this->m_player;
}
//------------------------------------------------------------------
const sf::Texture* FileManager::getDec(const int place) const
{
	return &this->m_dec[place];
}
//------------------------------------------------------------------

//get the decoration of the level
const sf::IntRect FileManager::getCurrLevDecRect(const levels currLevel,
	const decoration dec) const
{
	return this->m_decRect[currLevel - 1][dec];
}
//------------------------------------------------------------------

//get the decoration of the level
const sf::IntRect FileManager::getPlayerRect(const gender g) const
{
	return this->m_PlayerRect[g];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getStaticData(const icons object)const
{
	return m_staticData[object];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getMonstersData(const levels lev, 
	const icons object)const
{
	return m_monsterData[lev-1][object];
}
//------------------------------------------------------------------

const AnimationData& FileManager::getPlayerData(const gender g)const
{
	return m_playerData[g];
}
//----------------------- movableAnimationSet ------------------------
//		Set the Movable objects animations data, time and frequancy.

std::vector<sf::IntRect> FileManager::movableAnimationSet(
	const sf::Vector2i size,
	const sf::Vector2i startPos,
	const int space,
	const int count, const Operation typeOperation)
{
	auto stand_anime = AnimationData{};
	auto currentStart = startPos;
	sf::Vector2i currSize;

	currSize.x = size.x ;
	currSize.y = size.y;

	auto nextStart = [&]()
	{
		currentStart.x += currSize.x+space;
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

void FileManager::setCurrentData( AnimationData& data, const Operation op,
	const std::vector<sf::IntRect> inRect, const float time, const bool once)
{
	data.m_data[op] = inRect;
	data.m_time[op] = time;
	data.m_playOnce[op] = once;
}
//------------------------------------------------------------------------
// Set all animation data used in the game.

void FileManager::setAnimationsData()
{
	setCurrentData(m_staticData[DIAMOND], Stay, movableAnimationSet
	({ 110, 110 }, { 36,16 }, 15,7, Stay), 0.2f, false);

	createPlayerAnimeData();
	createForestMonstersAnimeData();
	createSnowMonstersAnimeData();
	createDesertMonstersAnimeData();
}

//--------------------------- playerAnime ----------------------------
//Set the player animations.

void FileManager::createPlayerAnimeData()
{
	setCurrentData(m_playerData[MALE], Stay, movableAnimationSet
	({ 112, 110 }, { 736, 5 },0, 1,Stay), 0.2f, false);

	setCurrentData(m_playerData[MALE], Walk, movableAnimationSet
	({ 118, 108 }, { 482, 5 }, 5,2, Walk), 0.02f, false);

	setCurrentData(m_playerData[MALE], Jump, movableAnimationSet
	({ 120, 115 }, { 365, 6 },0, 1,Jump), 0.15f, true);

	setCurrentData(m_playerData[MALE], Hit, movableAnimationSet
	({ 100, 105 }, { 133, 8 },20, 2, Hit), 0.06f, true);

	setCurrentData(m_playerData[MALE], Hurt, movableAnimationSet
	({ 112, 110 }, { 736, 5 }, 0, 2, Hurt), 0.03f, true);

	setCurrentData(m_playerData[MALE], Climbe, movableAnimationSet
	({ 100, 115 }, { 26, 4 }, 0, 1, Climbe), 0.05f, false);


	setCurrentData(m_playerData[FEMALE], Stay, movableAnimationSet
	({ 95, 110 }, { 734, 127 }, 0, 1, Stay), 0.2f, false);

	setCurrentData(m_playerData[FEMALE], Walk, movableAnimationSet
	({ 103, 108 }, { 490, 128 }, 25, 2, Walk), 0.02f, false);

	setCurrentData(m_playerData[FEMALE], Jump, movableAnimationSet
	({ 110, 108 }, { 384, 130 }, 0, 1, Jump), 0.15f, true);

	setCurrentData(m_playerData[FEMALE], Hit, movableAnimationSet
	({ 90, 105 }, { 136, 127 }, 25, 2, Hit), 0.06f, true);

	setCurrentData(m_playerData[FEMALE], Hurt, movableAnimationSet
	({ 95, 105 }, { 734, 127 }, 0, 2, Hurt), 0.03f, true);

	setCurrentData(m_playerData[FEMALE], Climbe, movableAnimationSet
	({ 110, 105 }, { 18, 126 }, 0, 1, Climbe), 0.05f, false);
	 
}
//--------------------------- monstersAnime ----------------------------
//Set the monsters animations.

void FileManager::createForestMonstersAnimeData()
{
	setCurrentData(m_monsterData[FOREST][MONSTER1], Stay, movableAnimationSet
	({ 60, 55 }, { 1, 1 }, 5, 3, Stay), 0.03f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER1], Walk, movableAnimationSet
	({ 60, 55 }, { 3, 60 }, 5, 4, Walk), 0.04f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER1], Hurt, movableAnimationSet
	({ 60, 55 }, { 4, 117 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[FOREST][MONSTER1], Dead, movableAnimationSet
	({ 60, 55 }, { 4, 182 }, 5, 4, Dead), 0.005f, true);
	

	setCurrentData(m_monsterData[FOREST][MONSTER2], Stay, movableAnimationSet
	({ 82, 82 }, { 1, 1 }, 5, 4, Stay), 0.03f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER2], Walk, movableAnimationSet
	({ 82, 82 }, { 1, 90 }, 5, 4, Walk), 0.04f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER2], Hurt, movableAnimationSet
	({ 82, 82 }, { 1, 177 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[FOREST][MONSTER2], Dead, movableAnimationSet
	({ 80, 70 }, { 1, 269 }, 4, 5, Dead), 0.005f, true);


	setCurrentData(m_monsterData[FOREST][MONSTER3], Stay, movableAnimationSet
	({ 102, 65 }, { 9, 6 }, 3, 3, Stay), 0.03f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER3], Walk, movableAnimationSet
	({ 97, 60 }, { 1, 80 }, 3, 4, Walk), 0.04f, false);

	setCurrentData(m_monsterData[FOREST][MONSTER3], Hurt, movableAnimationSet
	({ 90, 62 }, { 4, 222 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[FOREST][MONSTER3], Dead, movableAnimationSet
	({ 130, 50 }, { 8, 296 }, 0, 3, Dead), 0.005f, true);
}
//----------------------------------------------------

void FileManager::createSnowMonstersAnimeData()
{
	setCurrentData(m_monsterData[SNOW][MONSTER1], Stay, movableAnimationSet
	({ 34, 35 }, { 1, 7 },11,5, Stay), 0.03f, false);
	
	setCurrentData(m_monsterData[SNOW][MONSTER1], Walk, movableAnimationSet
	({ 37, 35 }, { 1, 53 }, 10, 6, Walk), 0.04f, false);

	setCurrentData(m_monsterData[SNOW][MONSTER1], Hurt, movableAnimationSet
	({ 37, 35 }, { 1, 96 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[SNOW][MONSTER1], Dead, movableAnimationSet
	({ 52, 30 }, { 1, 140 }, 0, 5, Dead), 0.005f, true);


	setCurrentData(m_monsterData[SNOW][MONSTER2], Stay, movableAnimationSet
	({ 112, 65 }, { 13, 36 },40,4, Stay), 0.03f, false);

	setCurrentData(m_monsterData[SNOW][MONSTER2], Walk, movableAnimationSet
	({ 125, 65 }, { 13, 145 }, 40, 3, Walk), 0.04f, false);

	setCurrentData(m_monsterData[SNOW][MONSTER2], Hurt, movableAnimationSet
	({ 110, 50 }, { 10, 260 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[SNOW][MONSTER2], Dead, movableAnimationSet
	({ 125, 50 }, { 10, 352 }, 32, 4, Dead), 0.005f, true);


	setCurrentData(m_monsterData[SNOW][MONSTER3], Stay, movableAnimationSet
	({ 38, 40 }, { 1, 6 }, 8,3, Stay), 0.03f, false);

	setCurrentData(m_monsterData[SNOW][MONSTER3], Walk, movableAnimationSet
	({ 45, 40 }, { 1, 56 }, 5, 4, Walk), 0.04f, false);

	setCurrentData(m_monsterData[SNOW][MONSTER3], Hurt, movableAnimationSet
	({ 38, 40 }, { 2, 105 }, 3, 2,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[SNOW][MONSTER3], Dead, movableAnimationSet
	({ 62, 40 }, { 4, 155 }, 0, 6, Dead), 0.005f, true);

}
//----------------------------------------------------

void FileManager::createDesertMonstersAnimeData()
{
	setCurrentData(m_monsterData[DESERT][MONSTER1], Stay, movableAnimationSet
	({ 67, 76 }, { 1, 5 },9, 6, Stay), 0.03f, false);

	setCurrentData(m_monsterData[DESERT][MONSTER1], Walk, movableAnimationSet
	({ 67, 80 }, { 1, 86 },9, 6, Walk), 0.04f, false);
	 
	setCurrentData(m_monsterData[DESERT][MONSTER1], Hurt, movableAnimationSet
	({ 67, 90 }, { 4, 166 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[DESERT][MONSTER1], Dead, movableAnimationSet
	({ 75, 90 }, { 7, 255 }, 0, 8, Dead), 0.005f, true);


	setCurrentData(m_monsterData[DESERT][MONSTER2], Stay, movableAnimationSet
	({ 48, 94 }, { 1, 1 },11,9, Stay), 0.03f, false);

	setCurrentData(m_monsterData[DESERT][MONSTER2], Walk, movableAnimationSet
	({ 49, 90 }, { 1, 92 }, 15, 4, Walk), 0.04f, false);

	setCurrentData(m_monsterData[DESERT][MONSTER2], Hurt, movableAnimationSet
	({ 49, 90 }, { 15, 180 }, 0, 1,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[DESERT][MONSTER2], Dead, movableAnimationSet
	({ 60, 100 }, { 13, 273 }, 10, 7, Dead), 0.005f, true);
	

	setCurrentData(m_monsterData[DESERT][MONSTER3], Stay, movableAnimationSet
	({ 55, 42 }, { 8, 11 }, 6,11, Stay), 0.03f, false);

	setCurrentData(m_monsterData[DESERT][MONSTER3], Walk, movableAnimationSet
	({ 55, 42 }, { 6, 67 }, 3,12, Walk), 0.04f, false);
	 
	setCurrentData(m_monsterData[DESERT][MONSTER3], Hurt, movableAnimationSet
	({ 55, 42 }, { 4, 217 }, 0, 1,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[DESERT][MONSTER3], Dead, movableAnimationSet
	({ 60, 66 }, { 7, 290 }, 0, 5, Dead), 0.005f, true);

}


