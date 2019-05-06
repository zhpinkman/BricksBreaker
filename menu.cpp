#include "menu.hpp"
#include "game.hpp"
#include <iostream>

using namespace std;

Menu::Menu():pointer(0), enter_pressed(0), exit (0)
{
	Button* button;
	for(int i = 0;i < 4; i++)
	{
		button = new Button(BUTTON_X, BUTTON_Y + i*BUTTON_DIST, BUTTON_WIDTH, BUTTON_HEIGHT);
		buttons.push_back(button);
	}
	buttons[0]->set_text("New game");
	buttons[1]->set_text("Edit username");
	buttons[2]->set_text("Score board");
	buttons[3]->set_text("Quit");
}
void Menu::initialize()
{
	enter_pressed = 0;
	exit = 0;
}
void Menu::draw_menu(Window* win, int& status)
{
	initialize();
	while(!enter_pressed )
	{
		cerr << "pinkman";
		update_event(win);
		if(exit)
			break;
		win->clear();
		win->draw_png(BACKGROUND, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		win->show_text("Brick breaker", TITLE_X, TITLE_Y, BLACK, MENU_TEXT_FONT, TITLE_FONT_SIZE);
		for(int i = 0;i < 4; i++)
		{
			buttons[i]->draw_button(win);
			buttons[i]->show_text_in(win);
			if(pointer == i)
				buttons[i]->draw_border(win);
		}
		win->update_screen();
		Delay(DELAY_TIME);
	}
	if(!exit)
		status = pointer;
	if(exit)
		status = EXIT;
}
void Menu::update_event(Window* win)
{
	event = win->pollForEvent();
	if(event.type() == QUIT)
		exit = 1;
	if(event.type() == KEY_PRESS)
	{
		if(event.pressedKey() == char(UP_ARROW))
			pointer--;
		else if(event.pressedKey() == char(DOWN_ARROW))
			pointer++;
		else if(event.pressedKey() == char(ENTER_KEY))
			enter_pressed = 1;
		else if(event.pressedKey() == char(ESC_KEY))
			exit = 1;
		pointer += 4;
		pointer %= 4;
	}
}
