#pragma once
#include <SFML/Graphics.hpp>

// general data
const unsigned int
NUM_OF_LEVELS = 3,
NUM_OF_STATIC_ICONS = 17, 
NUM_OF_BACKGROUNDSICONS=6,
NUM_OF_MONSTERS = 10,
NUM_OF_DEC = 17,
 NUM_OF_SOUNDS = 14, 
NUM_OF_BACKGROUNDS = 7,
NUM_OF_DIRECTION = 4,
NUM_OF_GIFT_TYPES = 4,
P_SIZE = 64; // pixel size


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
const int WINDOW_WIDTH = 1900,
WINDOW_HEIGHT = 900,
CAMERA_WIDTH = 360,
CAMERA_HEIGHT = 240;


//time data
const float GIFT_TIME = 30;
const int WIN_WIAT = 70;

//speed data
const float PLAYER_SPEED = 100.;
const float FAIRY_SPEED = 120;


// for the menu
const sf::Vector2f SCREEN_CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const int HEADER_SIZE = 80;
const int REG_CHAR_SIZE = 70;
const float OUTLINE_THICKNESS = 5.0;
const float BOLD_OUTLINE = 10.0;

// for the status bar
const int STATUS_BAR_HEIGHT = 50;
const int STATUS_BAR_CHAR_SIZE = 10;
const float STATUS_BAR_OUTLINE_THICKNESS = 3.0;
const int BUFF_DISTANCE = 40;
const sf::Vector2f MUSIC_ICON_SCALE = { 0.01f, 0.01f };

//direction data
const sf::Vector2f DVec[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

const char
PLAYER_C='P', EMPTY_C = ' ',
DIAMOND_C = 'D', GATE_C = '#', TELEPORT_C = 'X',
GIFT_C = '?', FAIRY_C = '^', FLOOR_C = '=', START_FLOOR_C = '(', END_FLOOR_C = ')',
F_TREE_C = 'T', S_TREE_C = 't',ROCK_C = 'R', BIG_MONSTER = 'B', MONSTER1_C = '1', MONSTER2_C = '2', MONSTER3_C = '3';

enum icons 
{
    MONSTER1, MONSTER2, MONSTER3, DIAMOND,
	WALL, FIRE, GATE, ORK, KEY, THRONE, TELEPORT, GIFT, FAIRY,POWER, LIFE,
	EMPTY
};

enum decoration
{
    L_FLOOR, M_FLOOR, R_FLOOR, F_TREE, S_TREE, ROCK
};
enum bIcons
{
    B_DIAMOND, B_POWER, B_LIFE,
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
	
};

enum direction
{
	LEFT, RIGHT, UP, DOWN,
};

const int STAGE_ONE = 1, STAGE_TWO = 2, STAGE_THREE = 3;

const sf::Vector2f SCALE_RIGHT{ -1,1 };
const sf::Vector2f SCALE_LEFT{ 1,1 };

enum Operation
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
    Dead,
    Max,
};

const sf::IntRect
LEFT_FLOOR_L1(341, 39, 55, 60),
MIDDLE_FLOOR_L1(405, 39, 55, 60),
RIGHT_FLOOR_L1(471, 39, 55, 60),
LEFT_FLOOR_L2(340, 178, 55, 50),
MIDDLE_FLOOR_L2(409, 178, 55, 50),
RIGHT_FLOOR_L2(477, 180, 55, 50),
LEFT_FLOOR_L3(342, 320, 52, 55),
MIDDLE_FLOOR_L3(403, 322, 50, 64),
RIGHT_FLOOR_L3(470, 320, 50, 50),
FIRST_TREE_L1(10, 11, 108, 88),
SECOUND_TREE_L1(116, 38, 77, 71),
ROCK_L1(204, 81, 40, 66),
FIRST_TREE_L2(10, 140, 106, 85),
SECOUND_TREE_L2(107, 142, 107, 67),
ROCK_L2(210, 196, 22, 30),
FIRST_TREE_L3(24, 282, 108, 76),
SECOUND_TREE_L3(107, 292, 96, 67),
ROCK_L3(195, 348, 40, 71);
