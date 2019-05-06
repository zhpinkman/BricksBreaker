#include "life_ball.hpp"
#include <iostream>

using namespace std;

Life_ball::Life_ball(double _x, double _y)
{
	x = _x;
	y = _y;
}
void Life_ball::draw_life_ball(Window* win)
{
	win->draw_png("lifeBall.png", x, y, 50, 50);
}
