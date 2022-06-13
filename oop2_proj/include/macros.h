#pragma once
#include <SFML/Graphics.hpp>

// general data
const unsigned int
NUM_OF_LEVELS = 3,
NUM_OF_SCREENS = 3,
NUM_OF_MONSTERS = 3,
NUM_OF_STATIC_ICONS = 20, 
NUM_OF_BACKGROUNDSICONS=6,
NUM_OF_DEC = 20,
 NUM_OF_SOUNDS = 14, 
NUM_OF_BACKGROUNDS = 7,
NUM_OF_DIRECTION = 4,
NUM_OF_GIFT_TYPES = 4,
P_SIZE = 64; // pixel size

const unsigned int
HITTING_POWER = 1,
LESS_LIFE = 1;

const unsigned int
MAX_LIFE = 1000,
MAX_POWER = 1000,
ADD_LIFE = 100,
ADD_POWER = 200;

//monster force
const  int
MON1_FORCE = 95,
MON2_FORCE = 45,
MON3_FORCE = 65,
PAYER_FORCE = 150,
PLAYER_DAMAGE = 5;


// sizes data
const int BLOCK_SIZE = 40;
const int X_SPACE = 40;
const int Y_SPACE = 17.7;
const int START_SPACE = 40;

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
const unsigned int BUTTON_VOLUME = 10; 

// window data
const int WINDOW_WIDTH = 1910,
WINDOW_HEIGHT = 950,
CAMERA_WIDTH = 360,
CAMERA_HEIGHT = 240;

//speed data
const float PLAYER_SPEED = 100.;
const float HANDLE_JUMP_SPEED = 80.f;

// for the menu
const sf::Vector2f SCREEN_CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
const int HEADER_SIZE = 80;
const int REG_CHAR_SIZE = 70;
const float OUTLINE_THICKNESS = 5.0;
const float BOLD_OUTLINE = 10.0;

// for the status bar
const int STATUS_BAR_HEIGHT = 50;
const int STATUS_BAR_CHAR_SIZE = 15;
const float STATUS_BAR_OUTLINE_THICKNESS = 3.0;
const int BUFF_DISTANCE = 40;
const sf::Vector2f MUSIC_ICON_SCALE = { 0.01f, 0.01f };

//color consts
const sf::Color
BASE_COLOR = sf::Color(153, 153, 255, 255),
OUTLINE_BASE_COLOR = sf::Color(0,0,0,255) ,
OUTLINE_MOVED_COLOR = sf::Color(230, 230, 255, 255),
OUTLINE_SELECTED_COLOR = sf::Color(0, 0, 77, 255),
HEADER_COLOR = sf::Color(204, 204, 255, 255);


// movement consts
const sf::Vector2f
UP_MOVEMENT(0, -1),
HEIGHT(0, 12),
LEFT_MOVEMENT(-1, 0),
RIGHT_MOVEMENT(1, 0),
DOWN_MOVEMENT(0, 1),
STAY_IN_PLACE(0, 0),
PUSH_FROM(10, 0),
PUSH_FROM_MONSTER(0.2, 0),
FALL_PUSH(0, 3),
MOVE_DOUBLE{ 2,0 };

//action counters:
const int
JUMP_COUNTER = 22,
HIT_COUNTER = 40;

// scale consts
const sf::Vector2f 
WALK_SCALE(0.9f, 1),
JUMP_SCALE(1.2f, 1),
HIT_SCALE(0.8f, 1),
HURT_SCALE(0.8f, 1),
SCALE_RIGHT{ -1,1 },
SCALE_LEFT{ 1,1 };

const float HALF_SIZE = 10.f;

const char
PLAYER_C='P', EMPTY_C = ' ',
DIAMOND_C = 'D', ROPE_C = '|', TELEPORT_C = 'X',
GIFT_C = '?', FAIRY_C = '^', FLOOR_C = '=', START_FLOOR_C = '(',
END_FLOOR_C = ')',F_TREE_C = 'T', S_TREE_C = 't',ROCK_C = 'R',
BIG_MONSTER = 'B', MONSTER1_C = '1', MONSTER2_C = '2',
MONSTER3_C = '3',GATE_C='#';

enum icons 
{
    MONSTER1, MONSTER2, MONSTER3, DIAMOND, GATE, TELEPORT,POWER, LIFE,POTION_L,
	POTION_P,ROPE,EMPTY
};

enum dec
{
	FLOOR_ROCK,
	TREE
};

enum Operation
{
	Up, Down, Right, Left, Stay, Hit,
	Jump, Fall, Walk, Hurt, Climbe, Dead,
};

enum backgroundsType
{
	MENU_BACKGROUND, LEVEL1_BACKGROUND, LEVEL2_BACKGROUND, LEVEL3_BACKGROUND,
	HELP_BACKGROUND, LOSE_LEVEL_BACKGROUND, WIN_GAME_BACKGROUND
};

enum sounds
{
	S_IN_TELEPORT, S_WIN_LEVEL, S_WIN_GAME, S_BACKROUND,
	S_TAKE_KEY, S_TAKE_DIAMOND, S_TAKE_POSION, S_ABOVE, S_CLICKED
};
enum gender { MALE, FEMALE ,WAIT };

enum screensOption { START,HELP, MENU,LOSE,WIN_GAME,WIN_LEVEL, RESTART, EXIT,NONE,CLOSE };

enum decoration{ L_FLOOR, M_FLOOR, R_FLOOR, F_TREE, S_TREE, ROCK };
   
enum bIcons{ B_DIAMOND, B_POWER, B_LIFE,};

enum levels{ LEVEL1,LEVEL2,LEVEL3};

enum posion{ POWERPOSION,  LIFE_POSION};

enum monster { M_FIRST,   M_SECOND, M_THIRD };

enum direction { LEFT, RIGHT, UP, DOWN };

enum playerSounds { WALK,JUMP,CLIME,};

enum monsterSounds{ HIT, HURT,};

const sf::IntRect
LEFT_FLOOR_L1(342, 40, 59, 55),
MIDDLE_FLOOR_L1(406, 40, 57, 55),
RIGHT_FLOOR_L1(476, 41, 60, 55),

LEFT_FLOOR_L2(353, 181, 45, 54),
MIDDLE_FLOOR_L2(406, 181, 45, 55),
RIGHT_FLOOR_L2(466, 181, 45, 55),

LEFT_FLOOR_L3(342, 322, 58, 50),
MIDDLE_FLOOR_L3(408, 322, 52, 49),
RIGHT_FLOOR_L3(475, 322, 54, 50),

FIRST_TREE_L1(3,47,98,100),
SECOUND_TREE_L1(106,3,144,143),
ROCK_L1(200, 81, 80, 48),

FIRST_TREE_L2(13,182,98,150),
SECOUND_TREE_L2(134,178,100,160),
ROCK_L2(209, 192, 40, 30),

FIRST_TREE_L3(1,402,104,100),
SECOUND_TREE_L3(116,376,122,132),
ROCK_L3(195, 348, 80, 50),

MALE_RECT(736, 5, 95, 110), 
FEMALE_RECT(734, 127, 95, 110),

CLOSE_GATE_RECT(15, 6, 320, 320),
OPEN_GATE_RECT(378, 6, 343, 320);

