#include "ScreensInclude\MenuScreen.h"


MenuScreen::MenuScreen()
{
	this->m_background.setTexture
	(FileManager::instance().getBackGround(MENU_BACKGROUND));

	setHeader();
	setStart();
	setExit();
	setHelp();
	setPick();
	setPlayer();
}
//------------------------------------------
//Draw all the buttons on the window

void MenuScreen::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(this->m_background);
	window.draw(this->m_header);
	window.draw(this->m_start);
	window.draw(this->m_exit);
	window.draw(this->m_boyplayer);
	window.draw(this->m_girlplayer);
	window.draw(this->m_help);
	window.draw(this->m_pick);

	window.display();
}
//------------------------------------------
//Handle click on the menu buttons

screensOption MenuScreen::handleClick(const sf::Vector2f& Location,
	sf::RenderWindow& window)
{
	// pressed start
	if (this->m_start.getGlobalBounds().contains(Location)) 
	{
		if (m_selectedPlayer != WAIT)
		{
			playSelectSound();
			return START;
		}
		FileManager::instance().startSound(FileManager::instance().getShareSaund(S_NO_PLAYER_SELECTED),
			VOLUME_COLLISION);
		this->m_pick.setOutlineColor(sf::Color::Red);
		this->m_pick.setOutlineThickness(BOLD_OUTLINE);
	}
	// pressed help
	if (this->m_help.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		return HELP;
	}
	// pressed players
	if (this->m_girlplayer.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		m_selectedPlayer = FEMALE;
		this->m_girlplayer.setOutlineColor(OUTLINE_SELECTED_COLOR);
		this->m_girlplayer.setOutlineThickness(BOLD_OUTLINE);
		this->m_boyplayer.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);

	}
	if (this->m_boyplayer.getGlobalBounds().contains(Location)) 
	{
		playSelectSound();
		m_selectedPlayer = MALE;
		this->m_boyplayer.setOutlineColor(OUTLINE_SELECTED_COLOR);
		this->m_boyplayer.setOutlineThickness(BOLD_OUTLINE);
		this->m_girlplayer.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);

	}
	// pressed exit
	if (this->m_exit.getGlobalBounds().contains(Location))	
	{
		playSelectSound();
		window.close();
	}
	return NONE;
}
//------------------------------------------
//Handle moving on the menu buttons

void MenuScreen::handleMove(const sf::Vector2f& Location)
{
	// mark/unmark start button
	if (this->m_start.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_start.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_start.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_start.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_start.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark exit button
	if (this->m_exit.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_exit.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_exit.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_exit.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_exit.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark help button
	if (this->m_help.getGlobalBounds().contains(Location))
	{
		playMoveSound();
		this->m_help.setOutlineColor(OUTLINE_MOVED_COLOR);
		this->m_help.setOutlineThickness(BOLD_OUTLINE);
	}
	else
	{
		this->m_help.setOutlineColor(OUTLINE_BASE_COLOR);
		this->m_help.setOutlineThickness(OUTLINE_THICKNESS);
	}
	// mark/unmark players button
	if (this->m_boyplayer.getOutlineColor() != OUTLINE_SELECTED_COLOR)
	{
		if (this->m_boyplayer.getGlobalBounds().contains(Location))
		{
			playMoveSound();
			this->m_boyplayer.setOutlineColor(OUTLINE_MOVED_COLOR);
			this->m_boyplayer.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{
			this->m_boyplayer.setOutlineColor(OUTLINE_BASE_COLOR);
			this->m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);
		}
	}
	if (this->m_girlplayer.getOutlineColor() != OUTLINE_SELECTED_COLOR)
	{
		if (this->m_girlplayer.getGlobalBounds().contains(Location))
		{
			playMoveSound();
			this->m_girlplayer.setOutlineColor(OUTLINE_MOVED_COLOR);
			this->m_girlplayer.setOutlineThickness(BOLD_OUTLINE);
		}
		else
		{
			this->m_girlplayer.setOutlineColor(OUTLINE_BASE_COLOR);
			this->m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);
		}
	}
	this->m_pick.setOutlineColor(OUTLINE_BASE_COLOR);
	this->m_pick.setOutlineThickness(OUTLINE_THICKNESS);
}
//------------------------------------------
//set the header details

void MenuScreen::setHeader()
{
	setBasicHeader(&m_header);
	m_header.setPosition({ WINDOW_WIDTH / 2 - 370, 30 });
	m_header.setString("The Diamonds Fighter");
}
//------------------------------------------
//set the start details

void MenuScreen::setStart()
{
	setBasicButton(&m_start);
	m_start.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y - 70 });
	m_start.setString("Start");

}
//------------------------------------------
//set the help details

void MenuScreen::setHelp()
{
	setBasicButton(&m_help);
	m_help.setPosition({ SCREEN_CENTER.x - 40, SCREEN_CENTER.y + 190 });
	m_help.setString("Help");
}
//------------------------------------------
//set the exit details

void MenuScreen::setExit()
{
	setBasicButton(&m_exit);
	m_exit.setPosition({ SCREEN_CENTER.x - 40 , SCREEN_CENTER.y + 60 });
	m_exit.setString("Exit");
}
//------------------------------------------
//set the pick text details

void MenuScreen::setPick()
{
	setBasicButton(&m_pick);
	m_pick.setPosition({ SCREEN_CENTER.x - 720 , SCREEN_CENTER.y - 200 });
	m_pick.setString("Pick a Character:");	
}
//------------------------------------------
//set the Players details

void MenuScreen::setPlayer()
{
	auto m_pTexture = FileManager::instance().getPlayerTexture();

	m_boyplayer.setTexture(m_pTexture);
	m_boyplayer.setTextureRect(FileManager::instance().getPlayerRect(MALE));
	m_boyplayer.setOutlineThickness(OUTLINE_THICKNESS);
	m_boyplayer.setOutlineColor(OUTLINE_BASE_COLOR);
	m_boyplayer.setPosition({ SCREEN_CENTER.x - 400 , SCREEN_CENTER.y - 60 });
	m_boyplayer.setSize({ BLOCK_SIZE * 4, BLOCK_SIZE * 4 });

	m_girlplayer.setTexture(m_pTexture);
	m_girlplayer.setTextureRect(FileManager::instance().getPlayerRect(FEMALE));
	m_girlplayer.setOutlineThickness(OUTLINE_THICKNESS);
	m_girlplayer.setOutlineColor(OUTLINE_BASE_COLOR);
	m_girlplayer.setPosition({ SCREEN_CENTER.x - 700 , SCREEN_CENTER.y - 60 });
	m_girlplayer.setSize({ BLOCK_SIZE*4, BLOCK_SIZE*4 });
}
//------------------------------------------
//Play the Background Sound

void MenuScreen::playBackgroundSound()
{
	if (!FileManager::instance().getIsMenuAudioPlaying())
	{
		FileManager::instance().startBackgraundSound(FileManager::instance().
			getShareSaund(S_MENU), VOLUME_BG);
		FileManager::instance().setIsMenuAudioPlaying(true);
	}
}