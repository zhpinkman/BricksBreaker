#ifndef NEW_GAME
#define NEW_GAME NEW_GAME

#include "rsdl.hpp"
#include "ball.hpp"
#include "brick.hpp"
#include <vector>
#include <string>
#include "life_ball.hpp"
#include "fire_ball.hpp"
#include "User.hpp"

using namespace std;

#define FROM_UP 2
#define FROM_RIGHT 3
#define FROM_LEFT 1
#define FROM_DOWN 0
#define ARROW_DIM 30
#define CROSS_DIM 10
#define CROSS_CH_BASE_X 10
#define ARROW_CH_BASE_X 0
#define CROSS_CH_BASE_Y 40
#define ARROW_CH_BASE_Y 10
#define ANGLE_CH_BASE 135
#define TEXT_X 10
#define TEXT_Y 3
#define TEXT_HEIGHT 35
#define DELAY_TIME 10
#define MAX_ANGLE 150
#define MIN_ANGLE 30
#define MAX_ROW 520
#define MAX_Y 628
#define MAX_X 470
#define MIN_Y 150
#define BALL_R 15
#define LIFE_BALL_R 15
#define FIRE_BALL_R 15
#define FIRE_BALL_BASE_X 30
#define FIRE_BALL_BASE_Y 160
#define FIRE_BALL_WIDTH 100
#define FIRE_BALL_HEIGHT 60
#define LIFE_BALL_BASE_X 30
#define LIFE_BALL_BASE_Y 160
#define LIFE_BALL_WIDTH 100
#define LIFE_BALL_HEIGHT 60
#define BRICK_BASE_X 10
#define BRICK_BASE_Y 160
#define BRICK_WIDTH 100
#define BRICK_HEIGHT 60
#define TEXT_FONT_SIZE 40
#define TOP_LINE_X 0
#define TOP_LINE_Y 150
#define BOTTOM_LINE_X 0
#define BOTTOM_LINE_Y 660
#define BALLS_TEXT_WIDTH 30
#define TEXT_DIST 100
#define FONT "in_game.ttf"

class New_game
{
public:
	New_game();
	void drop_things_better(Window* win, User* looser);
	void display(Window* win, int& status, User* looser);
	void move(Ball* ball, bool fire, Window* win);
	bool balls_returned();
	void update_event(Window* win);
	void explosion(int x, int y);
	void get_angle_step(Window* win, User* looser);
	void set_base_state();
	void game_flow(Window* win, User* looser);
	void brick_break(Ball* ball, bool fire, Window* win);
	void draw_temps(Window* win, int temp_x, int temp_y);
	void check_game_over();
	double get_distance(double x, double y, double X, double Y);
	void get_life_ball(Ball* ball);
	void get_fire_ball(Ball* ball);
	void spawn_bricks();
	void spawn_objects();
	bool check_full(int x_index, int y_index);
	bool has_brick(int x_index, int y_index);
	bool has_life_ball(int x_index, int y_index);
	bool has_fire_ball(int x_index, int y_index);
private:
	bool fire_return ;
	int game_status;
	Event event;
	bool space_pressed;
	int x;
	int y;
	bool fire_ball;
	double angle;
	vector<Fire_ball*> fire_balls;
	vector<Ball*> balls;
	vector<Life_ball*> life_balls;
	vector<Brick*> bricks;
	int score;
	string username;
	int record;
	bool game_over;
	int num_of_balls;
	int pre_num_of_balls;
	bool fire_ball_return ;
	bool first_return;
	bool exit;
	int level;
	bool click;
	int mouse_x;
	int mouse_y;
	bool double_fire;
};


#endif
