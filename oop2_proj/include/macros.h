#pragma once
#include <SFML/Graphics.hpp>

// general data
const unsigned int NUM_OF_ICONS = 14; 
const unsigned int NUM_OF_PLAYERS = 4; 
const unsigned int NUM_OF_SOUNDS = 14; 
const unsigned int NUM_OF_BACKGROUNDS = 7;
const unsigned int NUM_OF_DIRECTION = 4;
const unsigned int NUM_OF_GIFT_TYPES = 4;
const unsigned int P_SIZE = 64; // pixel size


// sizes data
const int BLOCK_SIZE = 40;

const sf::Vector2f
SMALL_MONSTER_SIZE = sf::Vector2f(BLOCK_SIZE * 0.8, BLOCK_SIZE * 0.8),
BIG_MONSTER_SIZE = sf::Vector2f(BLOCK_SIZE * 0.8, BLOCK_SIZE * 0.8),
PLAYER_SIZE = sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE),
HART_SIZE = sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE),
DIAMOND_SIZE = sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE),
TELEPORT_SIZE = sf::Vector2f(BLOCK_SIZE * 2, BLOCK_SIZE);

//volume data
const unsigned int VOLUME_BG = 5;
const unsigned int VOLUME_COLLISION = 6;

// window data
const int MAX_HEIGHT = 12;
const int MAX_WIDTH = 27;
const int WINDOW_WIDTH = MAX_WIDTH*P_SIZE;
const int WINDOW_HEIGHT = (MAX_HEIGHT+1) * P_SIZE;

//time data
const float GIFT_TIME = 30;
const int WIN_WIAT = 70;

//speed data
const float BASE_SPEED = 100.;
const float FAIRY_SPEED = 120;


// for the menu
const sf::Vector2f SCREEN_CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const int HEADER_SIZE = 80;
const int REG_CHAR_SIZE = 70;
const float OUTLINE_THICKNESS = 5.0;
const float BOLD_OUTLINE = 10.0;

// for the status bar
const int STATUS_BAR_HEIGHT = 50;
const int STATUS_BAR_CHAR_SIZE = 60;
const float STATUS_BAR_OUTLINE_THICKNESS = 3.0;
const int BUFF_DISTANCE = 40;
const sf::Vector2f MUSIC_ICON_SCALE = { 0.08f, 0.08f };

//direction data
const sf::Vector2f DVec[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

const char
PLAYER_C='P', EMPTY_C = ' ', KING_C = 'K', WARRIOR_C = 'W', THIEF_C = 'T', MAGE_C = 'M',
FIRE_C = '*', GATE_C = '#', ORK_C = '!', KEY_C = 'F', TELEPORT_C = 'X',
GIFT_C = '?', FAIRY_C = '^', WALL_C = '=',
THRONE_C = '@';

enum icons 
{
	KING, WARRIOR, THIEF, MAGE,THIEF_WITH_KEY,
	WALL, FIRE, GATE, ORK, KEY, THRONE, TELEPORT, GIFT, FAIRY,
	EMPTY
};

enum levels
{
    LEVEL1,LEVEL2,LEVEL3
};

enum sounds
{
	S_TOUCH_WALL, S_TURN_OFF_FIRE, S_GIFT, S_KILL_ORK, S_IN_TELEPORT,
	S_WIN_LEVEL, S_WIN_GAME, S_BACKROUND, S_TOUCH_FIRE, S_TOUCH_ORK,
	S_TOUCH_GATE, S_TAKE_KEY, S_OPEN_GATE, S_TOUCH_FAIRY
};

enum backgroundsType
{
	MENU_BACKGROUND, LEVEL1_BACKGROUND, LEVEL2_BACKGROUND, LEVEL3_BACKGROUND,
    HELP_BACKGROUND,WIN_LEVEL_BACKGROUND,
	WIN_GAME_BACKGROUND
};

enum giftType
{
	LIFE, POWER , DIAMOND
};

enum direction
{
	LEFT, RIGHT, UP, DOWN,
};

const int STAGE_ONE = 1, STAGE_TWO = 2, STAGE_THREE = 3;

enum class Operation
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    Hit,
    Jump,
    Fall,
    Land,
    Loading1,
    Loading2,
    Pick_up,
    Pick_up_Left,
    Pick_up_Right,
    Pick_up_Jump,
    Pick_up_Fall,
    Pick_up_Land,
    Pick_up_Idle,
    Diamond,
    Dead,
    Max,
};