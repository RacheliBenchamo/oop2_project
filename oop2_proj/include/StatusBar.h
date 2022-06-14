#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "macros.h"


class StatusBar
{
public:
	StatusBar();
	~StatusBar() {};

	void updateLevel(const bool);
	int getLevel() const;
	void setLevel(const int);
	void setIcons();
	void setMaxDiamonds(const int max) { m_maxDiamonds=max; }
	void draw(sf::RenderWindow&,const int ,const int,const int);
	void resetNumOfLevel();
	bool containsMusicIcon(const sf::Vector2f ) const;
	void setMusicIcon();
	bool containsStopAndPlayIcon(const sf::Vector2f ) const;
	void setStopAndPlayIcon();
	bool containsRestartIcon(const sf::Vector2f) const;
	void setRestartIcon();
	bool containsSoundIcon(const sf::Vector2f) const;
	void setSoundIcon();
	void updatePos(const sf::Vector2f);
	void changeMusicIcon();
	void changePlayIcon();
	void changeSoundIcon();
private:
	void setLevelText();
	void setDiamondCounter();
	void updateDiamondText(const int);
	void setCurrLifeRect();
	void setCurrPowerRect();
	void updateLifeAndPower(const int , const int );
	void drawIcons(sf::RenderWindow&);


	int m_level;
	int m_maxDiamonds = 0;
	sf::Text m_levelText;
	sf::Text m_diamondText;
	sf::Font m_font;
	sf::Sprite m_lifeIcon,
		m_powerIcon,
		m_diamondIcon,
		m_stopAndPlayIcon,
		m_musicIcon,
		m_resetIcon,
		m_soundIcon;
	sf::RectangleShape
		m_currLife,
		m_currPower,
		m_lifeFrame,
		m_powerFrame;
	
};

