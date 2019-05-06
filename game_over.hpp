#include "rsdl.hpp"
#include "button.hpp"
#include "User.hpp"

#define NEW_GAME_X 80
#define NEW_GAME_Y 500
#define MENU_X 280 
#define	MENU_Y 500
#define GAME_OVER_BUTTON_WIDTH 150
#define GAME_OVER_BUTTON_HEIGHT 80
#define GAME_OVER_X 60
#define GAME_OVER_Y 20
#define GAME_OVER_WINDOW_WIDTH 500
#define GAME_OVER_WINDOW_HEIGHT 700
#define GAME_OVER_FONT "game_over.ttf"
#define GAME_OVER_FONT_SIZE 100
#define DELAY_TIME 10
#define RIGHT_ARROW 79
#define LEFT_ARROW 80
#define DOWN_ARROW 81
#define UP_ARROW 82
#define ENTER_KEY 13
#define ESC_KEY 27
#define SPACE_KEY 32
#define SCORE_SIZE 30
#define SCORE_X 100
#define SCORE_Y 200

class Game_over
{
public:
	Game_over();
	void draw_game_over(Window* win, User* looser, int& status);
	void update_event(Window* win);
private:
	int pointer;
	Event event;
	Button* new_game;
	Button* menu;
	bool enter_pressed;
};