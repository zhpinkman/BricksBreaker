#include "score.hpp"


Score_board::Score_board()
{
	exit = 0;
	back = new Button(BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT);
	back->set_text("Back");
	User* x;
}
void Score_board::Sort()
{
	for (int i = 0; i<users.size(); i++)
		for (int j = i+1; j<users.size(); j++)
			if (users[i]->get_highscore()>users[j]->get_highscore())
			{
				swap(users[i],users[j]);
			}
}
User* Score_board::find_history(User* new_user)
{
	for(int i = 0;i < users.size() ; i++)
		if(users[i]->get_name() == new_user->get_name())
			return users[i];
	return new_user;
}
void Score_board::add_user(User* new_user)
{
	for(int i = 0;i < users.size() ; i++)
		if(users[i]->get_name() == new_user->get_name())
			return;
	if(users.size() > 4 )
	{
		if(users[0]->get_highscore() < new_user->get_highscore())
		{
			users.erase(users.begin());
			users.push_back(new_user);
			Sort();
		}
	}
	else
	{ 
		users.push_back(new_user);
		Sort();
	}
}

void Score_board::update_event(Window* win)
{
	event = win->pollForEvent();
	if(event.type() == QUIT)
		exit = 1;
	else if(event.type() == KEY_PRESS)
	{
		if(event.pressedKey() == char(ESC_KEY))
			exit = 1;
		else if(event.pressedKey() == char(ENTER_KEY))
			exit = 1;

	}
}
void Score_board::draw_scoreboard(Window* win)
{
	while(!exit)
	{
		update_event(win);
		win->clear();
		win->fill_rect(0, 0, SCORE_WINDOW_WIDTH, SCORE_WINDOW_HEIGHT, WHITE);
		win->show_text("Highscores", 60, 10, BLACK, SCORE_BOARD_FONT, 90);
		Sort();
		for(int i = 0;i < users.size() ; i++)
		{
			win->show_text(to_string(i+1) + "." + users[users.size() - i - 1]->get_name() , BASE_X, BASE_Y + i*HEIGHT_DIFF, BLACK, SCORE_BOARD_FONT, SCORE_BOARD_FONT_SIZE);
			win->show_text(to_string(users[users.size() - i - 1]->get_highscore()) , SCORE_BASE_X, BASE_Y + i*HEIGHT_DIFF, BLACK, SCORE_BOARD_FONT, SCORE_BOARD_FONT_SIZE);
		}	
		back->draw_button(win);
		back->draw_border(win);
		back->show_text_in(win, 1);
		win->update_screen();
		Delay(SCORE_DELAY_TIME);
	}
	exit = 0;
}