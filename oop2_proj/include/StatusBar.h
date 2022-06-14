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
	void setMaxDiamonds(const int max) { m_maxDiamonds=max; }
	void draw(sf::RenderWindow&,const int ,const int,const int);
	void resetNumOfLevel();
	bool containsMusicIcon(const sf::Vector2f ) const;
	void setMusicIcon(const bool);
	bool containsStopAndPlayIcon(const sf::Vector2f ) const;
	void setStopAndPlayIcon(const bool);
	bool containsRestartIcon(const sf::Vector2f) const;
	void setRestartIcon(const bool);
	bool containsSoundIcon(const sf::Vector2f) const;
	void setSoundIcon(const bool);
	void updatePos(const sf::Vector2f);

private:
	void setLevelText();
	void setDiamondCounter();
	void setMusicIcon();
	void setStopIcon();
	void setRestartIcon();
	void updateDiamondText(const int);
	void setCurrLifeRect();
	void setCurrPowerRect();
	void updateLifeAndPower(const int power, const int life);


	int m_level;
	int m_maxDiamonds = 0;
	sf::Text m_levelText;
	sf::Text m_diamondText;
	sf::Font m_font;
	sf::Sprite m_stopAndPlayIcon;
	sf::Sprite m_musicIcon;
	sf::Sprite m_resetIcon;
	sf::Sprite m_lifeIcon;
	sf::Sprite m_powerIcon;
	sf::Sprite m_diamondIcon;
	sf::RectangleShape
		m_currLife,
		m_currPower,
		m_lifeFrame,
		m_powerFrame;
};

