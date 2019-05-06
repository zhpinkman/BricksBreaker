#ifndef LIFE_BALL
#define LIFE_BALL LIFE_BALL

#include "rsdl.hpp"
#include "all_ball.hpp"

class Life_ball : public All_ball
{
public:
	Life_ball(double _x = 0, double _y = 0);
	void draw_life_ball(Window* win);
	void drop_one() { y++; }
private:
};


#endif
