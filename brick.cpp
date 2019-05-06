#include "brick.hpp"
#include <iostream>
#include <string>

using namespace std;

Brick::Brick(int _top_corner_x , int _top_corner_y, int _resistance, int _width , int _height  )
{
	top_corner_x = _top_corner_x;
	top_corner_y = _top_corner_y;
	width = _width;
	height = _height;
	resistance = _resistance;
	bomb = false;
}
void Brick::draw_brick(Window* win, int temp)
{
	srand(time(NULL));
	if(resistance > 0)
	{
		if(!bomb)
		{
			if(temp == 1)
			{
				RGB COLOR(rand()%MAX_COLOR, rand()%MAX_COLOR, rand()%MAX_COLOR);
				win->fill_rect(top_corner_x, top_corner_y, width, height, COLOR);
			}
			else if(temp == 0)
			{
				RGB COLOR((5*resistance)%MAX_COLOR, (10*resistance)%MAX_COLOR, (20*resistance)%MAX_COLOR);
				win->fill_rect(top_corner_x, top_corner_y, width, height, COLOR);
				win->show_text(to_string(resistance), top_corner_x + width/2, top_corner_y + height/3, BLUE, "OpenSans.ttf", 20);
			}
			else if(temp == 2)
				win->fill_rect(top_corner_x, top_corner_y, width, height, RED);
		}
		else
			win->fill_rect(top_corner_x, top_corner_y, width, height, BLACK);
	}
}
int Brick::check_impact(double x, double y, double vx, double vy)
{
	if( (x > top_corner_x - BALL_R  - BRICK_MARGIN && x < (top_corner_x + width + BALL_R + BRICK_MARGIN ) ) && (y > (top_corner_y + height) && y < (top_corner_y + height + (BALL_V+1))) )
	{
		if(vy < 0)
			return 0;
	}
	if( (y > top_corner_y - BALL_R - BRICK_MARGIN && y < (top_corner_y + height + BALL_R + BRICK_MARGIN )) && (x > (top_corner_x - 2*BALL_R - (BALL_V+1) ) && x < top_corner_x - 2*BALL_R ) )
	{
		if(vx > 0)
			return 1;
	}
	if( (x > top_corner_x - BALL_R - BRICK_MARGIN && x < (top_corner_x + width + BALL_R + BRICK_MARGIN )) && (y > top_corner_y - 2*BALL_R - (BALL_V+1) && y < top_corner_y - 2*BALL_R) )
	{
		if(vy > 0)
			return 2;
	}
	if( (y > top_corner_y  - BALL_R - BRICK_MARGIN && y < (top_corner_y + height + BALL_R + BRICK_MARGIN )) && (x > (top_corner_x + width) && x < (top_corner_x + width + (BALL_V+1))) )
	{
		if(vx < 0)
			return 3;
	}
}
