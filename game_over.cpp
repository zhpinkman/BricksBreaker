#include "game_over.hpp"

Game_over::Game_over()
{
	pointer = 0;
	new_game = new Button(NEW_GAME_X, NEW_GAME_Y, GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT);
	new_game->set_text("New game");
	menu = new Button(MENU_X, MENU_Y, GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT);
	menu->set_text("Menu");
	enter_pressed = 0;
}
void Game_over::update_event(Window* win)
{
	event = win->pollForEvent();
	if(event.type() == KEY_PRESS)
	{
		if(event.pressedKey() == char(LEFT_ARROW))
		{
			pointer--;
			pointer += 2;
			pointer %=2;
		}
		else if(event.pressedKey() == char(RIGHT_ARROW))
		{
			pointer++;
			pointer += 2;
			pointer %=2;
		}
		else if(event.pressedKey() == char(ENTER_KEY))
		{
			enter_pressed = 1;
		}
	}
}
void Game_over::draw_game_over(Window* win, User* looser,int& status)
{
	while(!enter_pressed)
	{
		win->clear();
		update_event(win);
		win->fill_rect(0, 0, GAME_OVER_WINDOW_WIDTH, GAME_OVER_WINDOW_HEIGHT, WHITE);
		win->show_text("Game Over!! :)", GAME_OVER_X, GAME_OVER_Y, BLACK, GAME_OVER_FONT, GAME_OVER_FONT_SIZE);
		win->show_text("score :  " + to_string(looser->get_score()), SCORE_X, SCORE_Y, BLACK, GAME_OVER_FONT, SCORE_SIZE);
		win->show_text("high score :  " + to_string(looser->get_highscore()), SCORE_X, SCORE_Y + SCORE_Y/2, BLACK, GAME_OVER_FONT, SCORE_SIZE);
		new_game->draw_button(win);
		new_game->show_text_in(win);
		if(!pointer)
		{
			new_game->draw_border(win);
		}
		menu->draw_button(win);
		menu->show_text_in(win);
		if(pointer)
		{
			menu->draw_border(win);
		}
		win->update_screen();
		Delay(DELAY_TIME);
	}
	if(!pointer)
		status = 0;
	else
		status = -1;
	enter_pressed = 0;
}