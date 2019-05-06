#ifndef GAME
#define GAME GAME

#include <cmath>
#include <sstream>
#include "User.hpp"
#include "rsdl.hpp"
#include "menu.hpp"
#include "New_game.hpp"
#include "edit.hpp"
#include "score.hpp"
#include "game_over.hpp"
#include <vector>
#include <fstream>

#define MAIN_MENU -1
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 700
#define DT 1
#define DX 10
#define PI 3.14159265
#define BALL_V 5
#define PLAY_GAME 0
#define EXIT 3
#define EDIT_USER 1
#define SCOREBOARD 2
#define RIGHT_ARROW 79
#define LEFT_ARROW 80
#define DOWN_ARROW 81
#define UP_ARROW 82
#define ENTER_KEY 13
#define ESC_KEY 27
#define SPACE_KEY 32

class Game
{
public:
	Game();
	void read_from_file();
	void write_to_file();
	void main_menu();
	void show_menu();
	void start_game();
	void edit_user();
	void scoreboard();
private:
	bool starting_game;
	Menu* menu;
	Edit* edit;
	Score_board* board;
	New_game* new_game;
	Game_over* over;
	Window* win;
	User* x;
	int status;
	bool user_log_in;
};

#endif