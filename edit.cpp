#include "edit.hpp"
#include <string>
#include <iostream>

using namespace std;

Edit::Edit(string current_name, char c)
{
	name = current_name ;
	pre_name = "";
	last_char = c;
	canceled = 0;
	saved = 0;
	back_space = 0;
	input = 0;
	display = new Button(EDIT_TEXT_X, EDIT_TEXT_Y, EDIT_TEXT_WIDTH, EDIT_TEXT_HEIGHT);
	save = new Button(SAVE_X, SAVE_Y, EDIT_BUTTON_WIDTH, EDIT_BUTTON_HEIGHT);
	cancel = new Button(CANCEL_X, CANCEL_Y, EDIT_BUTTON_WIDTH, EDIT_BUTTON_HEIGHT);
	save->set_text("save");
	cancel->set_text("cancel");
	pointer =  0;
	quit = 0;
}
void Edit::initialize()
{
	canceled = 0;
	saved = 0;
	back_space = 0;
	input = 0;
	pointer =  0;
	quit = 0;
}
void Edit::add_char()
{
	name += last_char;
	input = 0;
}
void Edit::delete_last_char()
{

	name = name.substr(0, name.size() - 1);
	back_space = 0;
}
void Edit::proccess_input()
{
	if(input)
		add_char();
	else if(back_space)
		delete_last_char();
}
void Edit::update_event(Window* win)
{
	event = win->pollForEvent();
	if(event.type() == QUIT)
		quit = 1;
	if(event.type() == KEY_PRESS)
	{
		if(event.pressedKey() == char(BACK_SPACE))
			back_space = 1;
		else if(event.pressedKey() == char(ENTER_KEY))
		{
			if(!pointer)
			{
				pre_name = name;
				saved = 1;
			}
			else
			{
				name = pre_name;
				canceled = 1;
			}
		}
		else if(event.pressedKey() == char(LEFT_ARROW))
		{
			pointer ++;
			pointer += 2;
			pointer %= 2;
		}
		else if(event.pressedKey() == char(RIGHT_ARROW))
		{
			pointer --;
			pointer += 2;
			pointer %= 2;
		}
		else
		{
			if(name.size() < MAX_LEN)
			{
				input = 1;
				last_char = event.pressedKey();
			}
		}
	}
}
void Edit::edit_menu(Window* win, bool& user_log_in, User* looser)
{
	initialize();
	while(1)
	{
		win->clear();
		update_event(win);
		if(quit || saved || canceled)
		{
			break;
		}

		display->set_text(name);

		win->draw_png(BACKGROUND, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		display->draw_button(win);
		display->show_text_in(win);

		save->draw_button(win);
		if(pointer == 0)
			save->draw_border(win);
		cancel->draw_button(win);
		if(pointer == 1)
			cancel->draw_border(win);
		save->show_text_in(win, 1);
		cancel->show_text_in(win, 1);

		proccess_input();

		win->update_screen();
		Delay(EDIT_DELAY_TIME);
	}
	if(is_empty())
	{
		user_log_in = 0;
		return;
	}
	else
	{
		user_log_in = 1;
		looser->set_name(name);
	}
}
bool Edit::is_empty()
{
	string temp = "";
	stringstream ss(name);
	ss >> temp;
	if(temp != "")
		return 0;
	else
		return 1;
}
