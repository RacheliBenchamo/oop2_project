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
	sf::Texture* getMonstersTexture(const icons,const levels);
	sf::Texture* getPlayerTexture();
	const sf::Texture* getPlayAndStopIcon(bool )const;
	const sf::SoundBuffer* getSound(sounds)const;
	const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Texture* getBIcons(bIcons)const;

	const sf::Font* getFont()const;
	const sf::Texture* getCurrLevDec(icons, int) const;
	const AnimationData& getStaticData(icons);
	const AnimationData& getPlayerData();


private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;


	void loadMovingObj();
	void loadStaticObj();
	void loadAudio();
	void loadMusicIcon();
	void loadStopAndPlayIcon();
	void loadResetIcon();
	void loadBackgrounds();
	void loadBackgroundIcons();


	void setAnimationsData();
	AnimationData createPlayerAnimeData();
	void setCurrentData(AnimationData& , Operation ,std::vector<sf::IntRect> , float , bool );
	std::vector<sf::IntRect> movableAnimationSet(const sf::Vector2i ,
		const sf::Vector2i ,const int , Operation);
	AnimationData createStaticAnimationData(const sf::Vector2i,const sf::Vector2i ,const int );


	//sf::Texture m_icons[NUM_OF_STATIC_ICONS];
	//sf::Texture m_staticIcon[NUM_OF_STATIC_ICONS];
	sf::Texture m_monstersIcon[NUM_OF_LEVELS][NUM_OF_MONSTERS];
	sf::Texture m_player;
	sf::Texture m_dec[NUM_OF_LEVELS][NUM_OF_DEC];
	sf::Texture m_sharedStaticIcon[NUM_OF_DEC];

	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_backgroundIcons[NUM_OF_BACKGROUNDSICONS];

	sf::Texture m_musicTexture[2];
	sf::Texture m_playStopTexture[2];
	sf::Texture m_restartIcon;

	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::Font m_font;
	AnimationData m_staticData[NUM_OF_DEC];
	AnimationData m_playerData;

};


