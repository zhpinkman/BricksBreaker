#ifndef MENU
#define MENU MENU
#include <vector>
#include "rsdl.hpp"
#include "button.hpp"

#define BUTTON_X 150
#define BUTTON_Y 150
#define BUTTON_DIST 120
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80
#define MENU_TEXT_FONT "menu.ttf"
#define MENU_TEXT_FONT_SIZE 54
#define BACKGROUND "background.png"
#define TITLE_X 70
#define TITLE_Y 30
#define TITLE_FONT_SIZE 50

#define EXIT 3

class Menu
{
public:
	Menu();
	void draw_menu(Window* win, int& status);
	void update_event(Window* win);
	void initialize();
private:
	int pointer;
	Event event;
	bool enter_pressed;
	bool exit;
	vector<Button*> buttons;
};

#endif
