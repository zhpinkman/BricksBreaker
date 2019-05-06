#ifndef FIRE_BALL
#define FIRE_BALL FIRE_BALL

#include "rsdl.hpp"
#include "all_ball.hpp"

class Fire_ball : public All_ball
{
public:
	Fire_ball(double _x = 0, double _y = 0);
	void draw_fire_ball(Window* win);
	void drop_one() { y++; }
private:
};


#endif
