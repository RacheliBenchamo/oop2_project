#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "macros.h"


class StatusBar
{
public:
	StatusBar();
	~StatusBar() {};

	void updateTime();
	void updateLevel(bool);
	int getLevel() const;
	void setLevel(int);
	void setMaxDiamonds(int max) { m_maxDiamonds=max; }
	float getTime() const;
	void resetTimer();
	void setTime(int);
	void draw(sf::RenderWindow&,const int ,const int,const int);
	void resetNumOfLevel();
	bool containsMusicIcon(const sf::Event&) const;
	void setMusicIcon(bool);
	bool containsStopAndPlayIcon(const sf::Event&) const;
	void setStopAndPlayIcon(bool);
	bool containsRestartIcon(const sf::Event&) const;
	void updatePos(sf::Vector2f);

private:
	void setLevelText();
	void setDiamondCounter();
	void setTimeText();
	void setMusicIcon();
	void setStopIcon();
	void setRestartIcon();
	void updateTimePassText();
	void updateDiamondText(const int);
	void setCurrLifeRect();
	void setCurrPowerRect();//50.f, 8.f
	void updateLifeAndPower(int power,int life);


	sf::Clock m_timer;
	float m_minutes;
	float m_seconds;
	int m_level;
	int m_maxDiamonds = 0;

	sf::Text m_timeText;
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

