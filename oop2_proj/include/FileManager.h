#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"
#include "AnimationData.h"


class FileManager
{
public:
	~FileManager() {};
	static FileManager& p2FileManager();

	 sf::Texture* getIconTexture(const icons );
	const sf::Texture* getPlayAndStopIcon(bool )const;
	const sf::SoundBuffer* getSound(sounds)const;
	const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Font* getFont()const;
	const sf::Texture* getLev1Dec(icons, levels) const;
	const AnimationData& staticData(icons);
	void setAnimationsData();


private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	void loadFromFileIcons();
	void loadDecoration();
	/*void loadLevel1Dec();
	void loadLevel2Dec();
	void loadLevel3Dec();*/
	void loadAudio();
	void loadMusicIcon();
	void loadStopAndPlayIcon();
	void loadResetIcon();
	void loadBackgrounds();

	sf::Texture m_icons[NUM_OF_ICONS];
	sf::Texture m_dec1[NUM_OF_ICONS];
	sf::Texture m_dec2[NUM_OF_ICONS];
	sf::Texture m_dec3[NUM_OF_ICONS];
	sf::Texture SharedDec[NUM_OF_ICONS];

	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_musicTexture[2];
	sf::Texture m_playStopTexture[2];
	sf::Texture m_restartIcon;
	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::Font m_font;
	std::vector<AnimationData> m_data;

};


