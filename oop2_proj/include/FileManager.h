#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"
#include "Animation.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>
#include <array>
#include<stdio.h>
#include <fstream>

class FileManager
{
public:
	~FileManager() =default;
	static FileManager& instance();

    sf::Texture* getSharedStaticTexture(const objects);
	sf::Texture* getMonstersTexture(const objects,const levels);
	sf::Texture* getPlayerTexture();
	sf::SoundBuffer* getPlayerSound(const playerSounds, const levels);
	sf::SoundBuffer* getMonsterSound(const monsterSounds, const  levels, const objects);
	sf::SoundBuffer* getBackgraundSaund(const levels);
	sf::SoundBuffer* getShareSaund(const sounds);
	const sf::Texture* getBackGround(const backgroundsType)const;
	const sf::Texture* getBIcons(const bIcons)const;
	sf::Texture* getIconsTexture();
	void  startSound(sf::SoundBuffer* sound,const int)const;
	void startBackgraundSound(sf::SoundBuffer* sound, const int volum)const;
	const sf::Font* getFont()const;
	const sf::Texture* getDec(const int) const;
	const sf::IntRect getCurrLevDecRect(const levels, const decoration) const;
	const sf::IntRect getPlayerRect(const gender) const;
	const AnimationData& getStaticData(const objects)const;
	const AnimationData& getMonstersData(const levels, const objects)const;
	const AnimationData& getPlayerData(const gender)const;
	bool getIsMenuAudioPlaying()const { return m_isMenuAudioPlaying; }
	void setIsMenuAudioPlaying(const bool is) { m_isMenuAudioPlaying = is; }
	void setBackgroundMusic();
	void setAudiodMusic();
	bool getToPlayAudio()const { return m_playAudio; }

private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	void loadMovingObj();
	void loadStaticObj();
	void loadStaticObjRect();
	void loadPlayerRect();
	void loadAudio();
	void loadStaticdAudio();
	void loadBackgroundAudio();
	void loadforestAudio();
	void loadSnowdAudio();
	void loadDesertdAudio();
	void loadPlayerAudio();
	void loadBackgrounds();
	void loadBackgroundIcons();
	void setAnimationsData();
	void createPlayerAnimeData();
	void createDesertMonstersAnimeData();
	void createSnowMonstersAnimeData();
	void createForestMonstersAnimeData();

	void setCurrentData( AnimationData& , const Operation ,
		const std::vector<sf::IntRect> , const float , const bool );
	std::vector<sf::IntRect> movableAnimationSet(const sf::Vector2i ,const sf::Vector2i 
		, const int ,const int , const Operation);

	sf::Texture m_monstersIcon[NUM_OF_LEVELS][NUM_OF_MONSTERS];
	sf::Texture m_player;
	sf::Texture m_sharedStaticIcon[NUM_OF_DEC];
	sf::Texture m_dec[2];
	sf::IntRect m_decRect[NUM_OF_LEVELS][NUM_OF_DEC];
	sf::IntRect m_PlayerRect[NUM_OF_PLAYERS];
	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_backgroundIcons[NUM_OF_BACKGROUNDSICONS];
	sf::Texture m_icons;
	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::SoundBuffer m_backGroundAudio[NUM_OF_LEVELS];
	sf::SoundBuffer m_playerAudio[NUM_OF_LEVELS][NUM_OF_SOUNDS];
	sf::SoundBuffer m_monstersAudio[NUM_OF_LEVELS][NUM_OF_SOUNDS][NUM_OF_MONSTERS];

	sf::Font m_font;
	AnimationData m_staticData[NUM_OF_DEC];
	AnimationData m_playerData[NUM_OF_PLAYERS];
	AnimationData m_monsterData[NUM_OF_LEVELS][NUM_OF_MONSTERS];
	bool m_isMenuAudioPlaying
		, m_playBackground, m_playAudio;
};


