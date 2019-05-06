#ifndef ALL_BALL
#define ALL_BALL ALL_BALL

class All_ball
{
public:
	All_ball(double _x = 0, double _y = 0)
	:x(_x), y(_y)
	{}
	double get_x() { return x; }
	double get_y() { return y; }
protected:
	double x;
	double y;
};

#endif
