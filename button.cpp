#include <iostream>
#include "button.hpp"

using namespace std;

Button::Button(int x, int y, int _width, int _height, string text)
{
	top_x = x;
	top_y = y;
	width = _width;
	height = _height;
	text_in = text;
}
void Button::draw_button(Window* win)
{
	win->draw_rect(top_x, top_y, width, height, BLACK);
}
void Button::draw_border(Window* win)
{
	win->draw_rect(top_x - MARGIN, top_y - MARGIN, width + 2*MARGIN, height + 2*MARGIN, BLACK);
}	
void Button::show_text_in(Window* win, bool x)
{
	if(x)
	{
		if(text_in != "")
			win->show_text(text_in, top_x + width/2 + EDIT_BASE_X, top_y + height/2 + EDIT_BASE_Y, BLACK, BUTTON_FONT, BUTTON_FONT_SIZE);
	}
	else
	{
		if(text_in != "")
			win->show_text(text_in, top_x + width/2 - TEXT_BASE_X, top_y + height/2 - TEXT_BASE_Y, BLACK, BUTTON_FONT, BUTTON_FONT_SIZE);
	}
}