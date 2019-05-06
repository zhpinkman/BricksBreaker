#ifndef BRICK
#define BRICK BRICK

#include "rsdl.hpp"

#define BALL_R 15
#define BALL_V 5
#define MAX_COLOR 256
#define BRICK_MARGIN 5
#define BASE_BRICK_WIDTH 80
#define BASE_BRICK_HEIGHT 40

class Brick
{
public:
	Brick(int _top_corner_x = 10, int _top_corner_y =  100, int _resistance = 1, int _width = BASE_BRICK_WIDTH, int _height = BASE_BRICK_HEIGHT);
	void draw_brick(Window* win, int temp = 0);
	int get_resistance() { return resistance; }
	int check_impact(double x, double y, double vx, double vy);
	void affect_impact() { resistance-- ; }
	bool is_ruined() { return !(resistance); }
	int get_row (){ return top_corner_y; }
	void set_bomb() { bomb = 1; }
	bool is_bomb() { return bomb; }
	int get_top_x() { return top_corner_x; }
	int get_top_y() { return top_corner_y; }
	void drop_one() { top_corner_y++; }
private:
	int top_corner_x;
	int top_corner_y;
	int width;
	int height;
	int resistance;
	bool bomb;
};

#endif
