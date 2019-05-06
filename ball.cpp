#include "ball.hpp"
#include "game.hpp"

Ball::Ball(double _x, double _y, double _V , double _angle)
{
	x = _x;
	y = _y;
	V = _V;
	returned = 0;
	angle = _angle;
	vx = -V*cos(angle*PI/BALL_MAX_ANGLE);
	vy = -V*sin(angle*PI/BALL_MAX_ANGLE);

}
void Ball::set_angle(double _angle)
{
	angle = _angle;
	vx = -V*cos(angle*PI/BALL_MAX_ANGLE);
	vy = -V*sin(angle*PI/BALL_MAX_ANGLE);
}
