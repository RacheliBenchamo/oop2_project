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
	void updateLevel(int, bool);
	int getLevel() const;
	void setLevel(int);
	float getTime() const;
	void resetTimer();
	void setTime(int);
	void draw(sf::RenderWindow& ,int);
	void resetNumOfLevel();
	bool containsMusicIcon(const sf::Event&) const;
	void setMusicIcon(bool);
	bool containsStopAndPlayIcon(const sf::Event&) const;
	void setStopAndPlayIcon(bool);
	bool containsRestartIcon(const sf::Event&) const;


private:
	void currPlayerDetail();
	void setCurrPlayerText();
	void setLevelText();
	void setTimeText();
	void setMusicIcon();
	void setStopIcon();
	void setRestartIcon();
	void updateTimePassText();
	void updateTimeLeftText();

	sf::Clock m_timer;
	float m_minutes;
	float m_seconds;
	int m_level;
	bool m_timelessLevel;

	sf::Text m_currPlayerText;
	sf::Text m_timeText;
	sf::Text m_levelText;
	sf::Font m_font;


	sf::Sprite m_stopAndPlayIcon;
	sf::Sprite m_musicIcon;
	sf::Sprite m_resetIcon;
	sf::Sprite m_playersSprite[4];
};

