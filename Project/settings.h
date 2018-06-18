#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"


enum Play_t
{
	SINGLE_PLAYER_P,
	MULTI_PLAYER_P
};

enum Language_t
{
	EN_L,
	HE_L
};

enum Sounds_t 
{
	EXPLOSION_S,
	PLOOP_S
};

enum Music_t 
{
	MAINMENU_S,
	MAPEDITOR_S,
	GAME_S,
	WIN_S,
	LOST_S
};
enum Difficulity_t
{
	EASY_D = 30,
	MEDIUM_D = 20,
	IMPOSSIBLE_D = 10
};

enum Mod_t
{
	M2D_M,
	M3D_M
};

enum ActionType_t
{
	DRAW_6_A,
	DRAW_4_A,
	DRAW_2_A,
	ERASE_MODE_A,
	RESET_MODE_A
};

enum Menus_t
{
	MAINMENU_M,
	HELPMENU_M,
	OPTIONSMENU_M,
	MAPMENU_M,
	END_MENU_M,
	CHOOSEREADYMENU_M,
	CHOOSEGAMETYPEMENU_M,
	PAUSEMENU_M,
};

const int WON = 22;
const int M_ROW = 10;
const int M_COL = 10;

const int LEFT_SMALL = 4;
const int LEFT_NIDDLE = 2;
const int LEFT_BIG = 1;

const int NUM_OF_FONTS = 3;
const int NUM_OF_LANGUAGES = 2;
const int NUM_OF_BOARDS = 5;
const int NUM_OF_BUTTONS = 11;
const int NUM_OF_SHIPS = 9;
const int NUM_OF_BACKGROUND = 12;
const int NUM_OF_EFFECTS = 6;

const sf::Vector2i NO_CHOOSE = { -1,-1 };/*@*/
const sf::Vector2i PAUSE_CHOOSE = { -2,-2 };/*@*/

const sf::Time CONNECT_TIME = sf::seconds(30);
const int MAX_NAME_LEN = 10;
const int SCREEN_HEIGHT = 1280;
const int SCREEN_WIDTH = 720;


/*
*	PacketType are the types of messages that the server need to received and send
*/

using PacketType = sf::Uint8;
const PacketType INITIAL_NAME_DATA = 0;
const PacketType WHOWON = 1;
const PacketType SERVER_MSG = 2;
const PacketType COORDINATE = 3;
const PacketType HIT = 4;
const PacketType GET_HIT = 5;
const PacketType SCORE = 6;
const PacketType TURN = 7;
const PacketType CAN_PLAY = 8;
const PacketType INITIAL_DATA = 9;
const PacketType GET_COORD = 10;

using PacketChat = sf::Uint8;
const PacketChat NAME = 0;
const PacketChat GMSG = 1;
const PacketChat SMSG = 2;