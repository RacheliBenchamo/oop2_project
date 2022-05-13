#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"
#include "Animation.h"


class FileManager
{
public:
	~FileManager() {};
	static FileManager& p2FileManager();

    sf::Texture* getSharedStaticTexture(const icons );
	sf::Texture* getMonstersTexture(const icons, levels);
	// sf::Texture* getPlayerTexture(const icons);
	const sf::Texture* getPlayAndStopIcon(bool )const;
	const sf::SoundBuffer* getSound(sounds)const;
	const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Font* getFont()const;
	const sf::Texture* getCurrLevDec(icons, levels) const;
	const AnimationData& getStaticData(icons);
	void setAnimationsData();


private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	AnimationData createStaticAnimationData(const sf::Vector2i,const sf::Vector2i ,const int );
	void loadMovingObj();
	void loadStaticObj();
	void loadAudio();
	void loadMusicIcon();
	void loadStopAndPlayIcon();
	void loadResetIcon();
	void loadBackgrounds();

	//sf::Texture m_icons[NUM_OF_STATIC_ICONS];
	//sf::Texture m_staticIcon[NUM_OF_STATIC_ICONS];
	sf::Texture m_monstersIcon[NUM_OF_LEVELS][NUM_OF_MONSTERS];
	sf::Texture m_player;
	sf::Texture m_dec[NUM_OF_LEVELS][NUM_OF_DEC];
	sf::Texture m_sharedStaticIcon[NUM_OF_DEC];

	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_musicTexture[2];
	sf::Texture m_playStopTexture[2];
	sf::Texture m_restartIcon;
	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::Font m_font;
	AnimationData m_staticData[NUM_OF_DEC];

};


