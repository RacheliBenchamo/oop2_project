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
	//m_backgroundIcons[B_RESTART].loadFromFile("resetButton.png");
}

// //--------------------------------------------------
// load all the object images

void FileManager::loadMovingObj()
{
	m_player.loadFromFile("Player.png");
	loadPlayerRect();

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
	m_sharedStaticIcon[POTION_L].loadFromFile("LifePotion.png");
	m_sharedStaticIcon[POTION_P].loadFromFile("PowerPotion.png");
	m_sharedStaticIcon[ROPE].loadFromFile("Rope.png");
	m_sharedStaticIcon[GATE].loadFromFile("Gate.png");


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
	//m_audio[S_GIFT].loadFromFile("giftSound.wav");
	m_audio[S_TAKE_DIAMOND].loadFromFile("pickUpDiamond.wav");
	m_audio[S_IN_TELEPORT].loadFromFile("InTeleportSound.wav");
	m_audio[S_TAKE_KEY].loadFromFile("takeKeySound.wav");
	m_audio[S_WIN_LEVEL].loadFromFile("winLevelSound.wav");
	m_audio[S_WIN_GAME].loadFromFile("winGameSound.wav");
	m_audio[S_TAKE_POSION].loadFromFile("potionDrinking.wav");
	m_audio[S_ABOVE].loadFromFile("button_hover_sound.wav");
	m_audio[S_CLICKED].loadFromFile("button_clicked_sound.wav");

	m_backGroundAudio[LEVEL1].loadFromFile("Level1backgraund.wav");
	m_backGroundAudio[LEVEL2].loadFromFile("Level2backgraund.wav");
	m_backGroundAudio[LEVEL3].loadFromFile("Level3backgraund.wav");

	//for 3 levels
	m_playerAudio[LEVEL1][WALK].loadFromFile("GrassWalking.wav");
	m_playerAudio[LEVEL1][JUMP].loadFromFile("potionDrinking.wav");
	m_playerAudio[LEVEL1][CLIME].loadFromFile("potionDrinking.wav");
	//m_playerAudio[LEVEL1][HURT].loadFromFile("pickUpDiamond.wav");

	m_playerAudio[LEVEL2][WALK].loadFromFile("IceWalking.wav");
	m_playerAudio[LEVEL2][JUMP].loadFromFile("potionDrinking.wav");
	m_playerAudio[LEVEL2][CLIME].loadFromFile("potionDrinking.wav");
	//m_playerAudio[LEVEL2][HURT].loadFromFile("takeKeySound.wav");

	m_playerAudio[LEVEL3][WALK].loadFromFile("SandWalking.wav");
	m_playerAudio[LEVEL3][JUMP].loadFromFile("potionDrinking.wav");
	m_playerAudio[LEVEL3][CLIME].loadFromFile("potionDrinking.wav");
	//m_playerAudio[LEVEL3][HURT].loadFromFile("takeKeySound.wav");

	//for each monster in each level
	//M_FIRST,
	//	M_SECOND,
	//	M_THIRD
	m_monstersAudio[LEVEL1][HIT][M_FIRST].loadFromFile("MushriHit.wav");
	m_monstersAudio[LEVEL1][HURT][M_FIRST].loadFromFile("MushriHurt.wav");
	m_monstersAudio[LEVEL1][HIT][M_SECOND].loadFromFile("TreetHit.wav");
	m_monstersAudio[LEVEL1][HURT][M_SECOND].loadFromFile("TreetHurt.wav");
	m_monstersAudio[LEVEL1][HIT][M_THIRD].loadFromFile("GreemonHit.wav");
	m_monstersAudio[LEVEL1][HURT][M_THIRD].loadFromFile("GreemonHurt.wav");

	m_monstersAudio[LEVEL2][HIT][M_FIRST].loadFromFile("PenguwulungHit.wav");
	m_monstersAudio[LEVEL2][HURT][M_FIRST].loadFromFile("PenguwulungHurt.wav");
	m_monstersAudio[LEVEL2][HIT][M_SECOND].loadFromFile("SnowolfHit.wav");
	m_monstersAudio[LEVEL2][HURT][M_SECOND].loadFromFile("SnowolfHurt.wav");
	m_monstersAudio[LEVEL2][HIT][M_THIRD].loadFromFile("YetteyeyHit.wav");
	m_monstersAudio[LEVEL2][HURT][M_THIRD].loadFromFile("YetteyeyHurt.wav");

	m_monstersAudio[LEVEL3][HIT][M_FIRST].loadFromFile("CactisHit.wav");
	m_monstersAudio[LEVEL3][HURT][M_FIRST].loadFromFile("CactisHurt.wav");
	m_monstersAudio[LEVEL3][HIT][M_SECOND].loadFromFile("SuricatiHit.wav");
	m_monstersAudio[LEVEL3][HURT][M_SECOND].loadFromFile("SuricatiHurt.wav");
	m_monstersAudio[LEVEL3][HIT][M_THIRD].loadFromFile("FroggoHit.wav");
	m_monstersAudio[LEVEL3][HURT][M_THIRD].loadFromFile("FroggoHurt.wav");



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

sf::SoundBuffer* FileManager::getPlayerSound(playerSounds sound, levels currLevel)
{
	return &m_playerAudio[currLevel-1][sound];

}
//--------------------------------------------

sf::SoundBuffer* FileManager::getMonsterSound(monsterSounds sound, levels currLevel, monster currMonster)
{
	return &m_monstersAudio[currLevel-1][sound][currMonster];
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getBackgraundSaund(levels currLevel)
{
	return &this->m_backGroundAudio[currLevel];
}
//--------------------------------------------

sf::SoundBuffer* FileManager::getShareSaund(sounds sound)
{
	return &this->m_audio[sound];
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
	return &this->m_monstersIcon[currLevel-1][place];
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

//get the decoration of the level
const sf::IntRect FileManager::getPlayerRect(gender g) const
{
	return this->m_PlayerRect[g];
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

const AnimationData& FileManager::getPlayerData(gender g)
{
	return m_playerData[g];
}
//----------------------- movableAnimationSet ------------------------
//		Set the Movable objects animations data, time and frequancy.

std::vector<sf::IntRect> FileManager::movableAnimationSet(
	const sf::Vector2i size,
	const sf::Vector2i startPos,
	const int space,
	const int count, Operation typeOperation)
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
	({ 118, 108 }, { 482, 5 }, 5,2, Walk), 0.008f, false);

	setCurrentData(m_playerData[MALE], Jump, movableAnimationSet
	({ 118, 115 }, { 365, 6 },0, 1,Jump), 0.15f, true);

	setCurrentData(m_playerData[MALE], Hit, movableAnimationSet
	({ 100, 105 }, { 133, 8 },20, 2, Hit), 0.06f, true);

	setCurrentData(m_playerData[MALE], Hurt, movableAnimationSet
	({ 112, 110 }, { 736, 5 }, 0, 2, Hurt), 0.008f, true);

	setCurrentData(m_playerData[MALE], Climbe, movableAnimationSet
	({ 100, 115 }, { 26, 4 }, 0, 1, Climbe), 0.05f, false);


	setCurrentData(m_playerData[FEMALE], Stay, movableAnimationSet
	({ 95, 110 }, { 734, 127 }, 0, 1, Stay), 0.2f, false);

	setCurrentData(m_playerData[FEMALE], Walk, movableAnimationSet
	({ 103, 108 }, { 490, 128 }, 25, 2, Walk), 0.008f, false);

	setCurrentData(m_playerData[FEMALE], Jump, movableAnimationSet
	({ 100, 108 }, { 384, 130 }, 0, 1, Jump), 0.15f, true);

	setCurrentData(m_playerData[FEMALE], Hit, movableAnimationSet
	({ 90, 105 }, { 136, 127 }, 25, 2, Hit), 0.06f, true);

	setCurrentData(m_playerData[FEMALE], Hurt, movableAnimationSet
	({ 95, 105 }, { 734, 127 }, 0, 2, Hurt), 0.008f, true);

	setCurrentData(m_playerData[FEMALE], Climbe, movableAnimationSet
	({ 110, 105 }, { 18, 126 }, 0, 1, Climbe), 0.05f, false);
	 
}
//--------------------------- monstersAnime ----------------------------
//Set the monsters animations.

void FileManager::createForestMonstersAnimeData()
{
	setCurrentData(m_monsterData[LEVEL1][MONSTER1], Stay, movableAnimationSet
	({ 60, 55 }, { 1, 1 }, 5, 3, Stay), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER1], Walk, movableAnimationSet
	({ 60, 55 }, { 3, 60 }, 5, 4, Walk), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER1], Hurt, movableAnimationSet
	({ 60, 55 }, { 4, 117 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL1][MONSTER1], Dead, movableAnimationSet
	({ 60, 55 }, { 4, 182 }, 5, 4, Dead), 0.005f, true);
	

	setCurrentData(m_monsterData[LEVEL1][MONSTER2], Stay, movableAnimationSet
	({ 82, 82 }, { 1, 1 }, 5, 4, Stay), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER2], Walk, movableAnimationSet
	({ 82, 82 }, { 1, 90 }, 5, 4, Walk), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER2], Hurt, movableAnimationSet
	({ 82, 82 }, { 1, 177 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL1][MONSTER2], Dead, movableAnimationSet
	({ 80, 70 }, { 1, 269 }, 4, 5, Dead), 0.005f, true);


	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Stay, movableAnimationSet
	({ 102, 65 }, { 9, 6 }, 3, 3, Stay), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Walk, movableAnimationSet
	({ 97, 60 }, { 1, 80 }, 3, 4, Walk), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Hurt, movableAnimationSet
	({ 90, 62 }, { 4, 222 }, 0, 1, Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL1][MONSTER3], Dead, movableAnimationSet
	({ 130, 50 }, { 8, 296 }, 0, 3, Dead), 0.005f, true);
}
//----------------------------------------------------

void FileManager::createSnowMonstersAnimeData()
{
	setCurrentData(m_monsterData[LEVEL2][MONSTER1], Stay, movableAnimationSet
	({ 34, 35 }, { 1, 7 },11,5, Stay), 0.01f, false);
	
	setCurrentData(m_monsterData[LEVEL2][MONSTER1], Walk, movableAnimationSet
	({ 37, 35 }, { 1, 53 }, 10, 6, Walk), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL2][MONSTER1], Hurt, movableAnimationSet
	({ 37, 35 }, { 1, 96 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL2][MONSTER1], Dead, movableAnimationSet
	({ 52, 30 }, { 1, 140 }, 0, 5, Dead), 0.005f, true);


	setCurrentData(m_monsterData[LEVEL2][MONSTER2], Stay, movableAnimationSet
	({ 112, 65 }, { 13, 36 },40,4, Stay), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL2][MONSTER2], Walk, movableAnimationSet
	({ 125, 65 }, { 13, 145 }, 40, 3, Walk), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL2][MONSTER2], Hurt, movableAnimationSet
	({ 110, 50 }, { 10, 260 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL2][MONSTER2], Dead, movableAnimationSet
	({ 125, 50 }, { 10, 352 }, 32, 4, Dead), 0.005f, true);


	setCurrentData(m_monsterData[LEVEL2][MONSTER3], Stay, movableAnimationSet
	({ 38, 40 }, { 1, 6 }, 8,3, Stay), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL2][MONSTER3], Walk, movableAnimationSet
	({ 45, 40 }, { 1, 56 }, 5, 4, Walk), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL2][MONSTER3], Hurt, movableAnimationSet
	({ 38, 40 }, { 2, 105 }, 3, 2,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL2][MONSTER3], Dead, movableAnimationSet
	({ 62, 40 }, { 4, 155 }, 0, 6, Dead), 0.005f, true);

}
//----------------------------------------------------

void FileManager::createDesertMonstersAnimeData()
{
	setCurrentData(m_monsterData[LEVEL3][MONSTER1], Stay, movableAnimationSet
	({ 67, 76 }, { 1, 5 },9, 6, Stay), 0.02f, false);

	setCurrentData(m_monsterData[LEVEL3][MONSTER1], Walk, movableAnimationSet
	({ 67, 80 }, { 1, 86 },9, 6, Walk), 0.02f, false);
	 
	setCurrentData(m_monsterData[LEVEL3][MONSTER1], Hurt, movableAnimationSet
	({ 67, 90 }, { 4, 166 }, 0, 1,	Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL3][MONSTER1], Dead, movableAnimationSet
	({ 75, 90 }, { 7, 255 }, 0, 8, Dead), 0.005f, true);


	setCurrentData(m_monsterData[LEVEL3][MONSTER2], Stay, movableAnimationSet
	({ 48, 94 }, { 1, 1 },11,9, Stay), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL3][MONSTER2], Walk, movableAnimationSet
	({ 49, 90 }, { 1, 92 }, 15, 4, Walk), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL3][MONSTER2], Hurt, movableAnimationSet
	({ 49, 90 }, { 15, 180 }, 0, 1,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL3][MONSTER2], Dead, movableAnimationSet
	({ 60, 100 }, { 13, 273 }, 10, 7, Dead), 0.005f, true);
	

	setCurrentData(m_monsterData[LEVEL3][MONSTER3], Stay, movableAnimationSet
	({ 55, 42 }, { 8, 11 }, 6,11, Stay), 0.01f, false);

	setCurrentData(m_monsterData[LEVEL3][MONSTER3], Walk, movableAnimationSet
	({ 55, 42 }, { 6, 67 }, 3,12, Walk), 0.01f, false);
	 
	setCurrentData(m_monsterData[LEVEL3][MONSTER3], Hurt, movableAnimationSet
	({ 55, 42 }, { 4, 217 }, 0, 1,Hurt), 0.05f, true);

	setCurrentData(m_monsterData[LEVEL3][MONSTER3], Dead, movableAnimationSet
	({ 60, 66 }, { 7, 290 }, 0, 5, Dead), 0.005f, true);

}

