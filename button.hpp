#ifndef BUTTON
#define BUTTON BUTTON

#include "rsdl.hpp"

using namespace std;

#define BUTTON_X 150
#define BUTTON_Y 150
#define BUTTON_DIST 120
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80
#define BUTTON_FONT "OpenSans.ttf"
#define BUTTON_FONT_SIZE 20
#define TEXT_BASE_X 60
#define TEXT_BASE_Y 20
#define EDIT_BASE_X -35
#define EDIT_BASE_Y -15
#define MARGIN 10

class Button
{
public:
	Button(int x = BUTTON_X, int y = BUTTON_Y, int _width = BUTTON_WIDTH, int _height = BUTTON_HEIGHT, string text = "");
	void draw_button(Window* win);
	void draw_border(Window* win);
	void show_text_in(Window* win, bool x = 0);
	void set_text(string text) { text_in = text; }
private:
	int top_x;
	int top_y;
	int width;
	int height;
	string text_in;
};


#endif