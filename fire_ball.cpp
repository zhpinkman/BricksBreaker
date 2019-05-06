#include "fire_ball.hpp"
#include <iostream>

using namespace std;

Fire_ball::Fire_ball(double _x, double _y)
{
	x = _x;
	y = _y;
}

void Fire_ball::draw_fire_ball(Window* win)
{
	win->draw_png("fireBall.png", x, y, 30, 30);
}
