#include "game.hpp"
#include <algorithm>

Game::Game()
{
	win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "BRICK BREAKER");
	menu = new Menu();
	new_game = new New_game();
	edit = new Edit();
	board = new Score_board();
	status = MAIN_MENU;
	x = new User();
	user_log_in = 0;
	over = new Game_over();
	starting_game = 0;

}
void Game::main_menu()
{
	read_from_file();
	while(1)
	{
		if(status == EXIT)
		{
			break;
		}
		else if(status == MAIN_MENU)
		{
			show_menu();
		}
		else if(status == PLAY_GAME)
		{
			start_game();
		}
		else if(status == EDIT_USER)
		{
			edit_user();
		}

		else if(status == SCOREBOARD)
		{
			scoreboard();
		}
	}
	write_to_file();
}
void Game::show_menu()
{
	menu->draw_menu(win, status);
}
void Game::start_game()
{
	if(user_log_in == 0)
	{
		status = EDIT_USER;
		starting_game = 1;
		return;
	}

	x = board->find_history(x);
	new_game->display(win, status, x);
	over->draw_game_over(win, x, status);
	board->add_user(x);
	x->set_score(0);
	new_game = new New_game();
	starting_game = 0;
}
void Game::edit_user()
{
	edit->edit_menu(win, user_log_in, x);
	if(starting_game && user_log_in)
		status = PLAY_GAME;
	else
		status = MAIN_MENU;
}
void Game::scoreboard()
{
	board->draw_scoreboard(win);
	status = MAIN_MENU;
}
void Game::read_from_file()
{
	User* x;
	string line;
	string temp;
	int high_score;
	ifstream read("saved.txt");
	if(read.fail())
		return;
	while(getline(read, line))
	{
		x = new User();
		stringstream info(line);
		getline(info, temp, ',');
		x->set_name(temp);
		getline(info, temp);
		x->set_highscore(stoi(temp));
		board->add_user(x);
	}
}
void Game::write_to_file()
{
	ofstream write("saved.txt", ios::trunc);
	vector<User*> users(board->get_users());
	for(int i = 0;i < users.size(); i++)
	{
		write << users[i]->get_name() << "," << users[i]->get_highscore() << endl;
	}
}
