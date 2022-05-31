#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"
#include "Animation.h"
#include <chrono>
#include <thread>
#include <iostream>



class FileManager
{
public:
	~FileManager() {};
	static FileManager& instance();

    sf::Texture* getSharedStaticTexture(const icons );
	sf::Texture* getMonstersTexture(const icons,const levels);
	sf::Texture* getPlayerTexture();
	const sf::Texture* getPlayAndStopIcon(bool )const;
	void playSound(sounds)const;
	const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Texture* getBIcons(bIcons)const;

	const sf::Font* getFont()const;
	const sf::Texture* getDec() const;
	const sf::IntRect getCurrLevDecRect(levels, decoration) const;
	const AnimationData& getStaticData(icons);
	const AnimationData& getMonstersData(levels,icons);
	const AnimationData& getPlayerData();


private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	void loadMovingObj();
	void loadStaticObj();
	void loadStaticObjRect();
	void loadAudio();
	void loadMusicIcon();
	void loadStopAndPlayIcon();
	void loadResetIcon();
	void loadBackgrounds();
	void loadBackgroundIcons();

	void setAnimationsData();
	void createPlayerAnimeData();
	void createDesertMonstersAnimeData();
	void createSnowMonstersAnimeData();
	void createForestMonstersAnimeData();

	void setCurrentData(AnimationData& , Operation ,std::vector<sf::IntRect> , float , bool );
	std::vector<sf::IntRect> movableAnimationSet(const sf::Vector2i ,const sf::Vector2i , const int ,const int , Operation);

	sf::Texture m_monstersIcon[NUM_OF_LEVELS][NUM_OF_MONSTERS];
	sf::Texture m_player;
	sf::Texture m_sharedStaticIcon[NUM_OF_DEC];
	sf::Texture m_dec;
	sf::IntRect m_decRect[NUM_OF_LEVELS][NUM_OF_DEC];
	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_backgroundIcons[NUM_OF_BACKGROUNDSICONS];
	sf::Texture m_musicTexture[2];
	sf::Texture m_playStopTexture[2];
	sf::Texture m_restartIcon;

	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::SoundBuffer m_backGroundAudio[NUM_OF_LEVELS];
	sf::SoundBuffer m_playerAudio[NUM_OF_LEVELS][NUM_OF_SOUNDS];
	sf::SoundBuffer m_monstersAudio[NUM_OF_LEVELS][NUM_OF_SOUNDS];

	sf::Font m_font;

	AnimationData m_staticData[NUM_OF_DEC];
	AnimationData m_playerData;
	AnimationData m_monsterData[NUM_OF_LEVELS][NUM_OF_MONSTERS];
};


