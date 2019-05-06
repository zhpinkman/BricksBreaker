#ifndef BALL
#define BALL BALL
#define BALL_V 5
#define BALL_MAX_ANGLE 180
#include "all_ball.hpp"

class Ball : public All_ball
{
public:
	Ball(double _x = 0, double _y = 0, double _V = BALL_V, double _angle = 90);
	double get_vx() { return vx; }
	double get_vy() { return vy; }
	void set_x(double _x) { x = _x; }
	void set_y(double _y) { y = _y; }
	void reflect_y() { vy = -vy; }
	void reflect_x() { vx = -vx; }
	void set_angle(double _angle);
	bool get_return() { return returned; }
	void set_return(bool status) { returned = status; }
private:
	double V;
	double angle;
	bool returned;
	double vx;
	double vy;
};

#endif
