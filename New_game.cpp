#include "rsdl.hpp"
#include "New_game.hpp"
#include "game.hpp"
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

New_game::New_game()
{
	y = 630;
	x = 250;
	fire_return = 0;
	angle = 90;
	score = 1;
	game_over = 0;
	space_pressed = 0;
	num_of_balls = 1;
	pre_num_of_balls = 1;
	fire_ball = 0;
	exit = 0;
	first_return = 0;
	game_status = -1;
	level = 1;
	click = 0;
	double_fire = 0;
}
void New_game::drop_things_better(Window* win, User* looser)
{
	Ball* ball;
	while(num_of_balls > pre_num_of_balls)
	{
		pre_num_of_balls++;
		ball = new Ball(x, y, BALL_V, angle);
		balls.push_back(ball);
	}
	angle = 90;
	string ball_nums;
	int num = 0;
	ball_nums = to_string(balls.size());
	while(num != 60)
		{
			num++;
			win->clear();
			win->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
			win->show_text("username :  " + looser->get_name(), TEXT_X, TEXT_Y, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("highscore : " + to_string(looser->get_highscore()), TEXT_X, TEXT_Y + TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("Score : " + to_string(looser->get_score()), TEXT_X, TEXT_Y + 2* TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->draw_line(TOP_LINE_X, TOP_LINE_Y, WINDOW_WIDTH, TOP_LINE_Y, BLACK);
			win->draw_line(TOP_LINE_X, BOTTOM_LINE_Y, WINDOW_WIDTH, BOTTOM_LINE_Y, BLACK);
			for(int i = 0;i < bricks.size(); i++)
				bricks[i]->drop_one();
			for(int i = 0;i < life_balls.size(); i++)
				life_balls[i]->drop_one();
			for(int i = 0;i < fire_balls.size(); i++)
				fire_balls[i]->drop_one();
			for(int i = 0 ;i < bricks.size(); i++)
				bricks[i]->draw_brick(win);
			for(int i = 0;i < life_balls.size(); i++)
				life_balls[i]->draw_life_ball(win);
			for(int i = 0;i < fire_balls.size(); i++)
				fire_balls[i]->draw_fire_ball(win);
			if(!game_over)
			{
				win->draw_png("arrow.png",x - ARROW_CH_BASE_X, y - ARROW_CH_BASE_Y, ARROW_DIM, ARROW_DIM, angle-ANGLE_CH_BASE);
				if(fire_ball)
					win->draw_png("fireBall.png", x, y, 2*FIRE_BALL_R, 2*FIRE_BALL_R);
				else
					win->draw_png("ball.png", x, y, 2*BALL_R, 2*BALL_R);
				win->show_text(ball_nums, x , y + BALLS_TEXT_WIDTH, RED, FONT, TEXT_FONT_SIZE);
				win->draw_png("cross.png", x + CROSS_CH_BASE_X, y + CROSS_CH_BASE_Y, CROSS_DIM, CROSS_DIM);
			}
			win->update_screen();
			Delay(10);
		}
}
void New_game::display(Window* win, int& status, User* looser)
{
	Ball* ball;
	ball = new Ball(x, y, BALL_V, angle);
	balls.push_back(ball);
	while(1)
	{
		drop_things_better(win, looser);
		angle = 90;
		spawn_bricks();
		spawn_objects();
		looser->set_score(level);
		get_angle_step(win, looser);
		if(exit || game_over)
			break;
		set_base_state();

		game_flow(win, looser);

		check_game_over();
		level++;
	}
	game_over = 0;
	status = game_status;
}
void New_game::explosion(int x, int y)
{
	vector<int> index;
	int x_index = (x - BRICK_BASE_X)/BRICK_WIDTH ;
	int y_index = (y - BRICK_BASE_Y)/BRICK_HEIGHT ;
	for(int i = 0; i< bricks.size() ; i++)
	{
		for(int k = -1;k < 2; k++)
			if(bricks[i]->get_top_y() == (y_index + k)*BRICK_HEIGHT + BRICK_BASE_Y )
				for(int j = -1;j < 2; j++)
					if(bricks[i]->get_top_x() == (x_index + j)*BRICK_WIDTH + BRICK_BASE_X)
						index.push_back(i);
	}
	for(int i = 0;i < index.size(); i++)
	{
		bricks.erase(bricks.begin() + index[i]);
		for(int j = 0; j < index.size() ; j++)
		{
			index[j]--;
		}
	}
}
void New_game::draw_temps(Window* win, int temp_x, int temp_y)
{
	for(int i = 0;i < 9; i++)
	{
		Brick* temp_brick = new Brick(temp_x + 4*i, temp_y + 2*i, 1, 80 - 8*i, 40 - 4*i);
		temp_brick->draw_brick(win, 1);
		win->update_screen();
		Delay(3);
	}
}
void New_game::brick_break(Ball* ball, bool fire, Window* win)
{
	int temp_x;
	int temp_y;
	bool bomb_explode = false;
	for(int i = 0 ;i < bricks.size(); i++)
	{
		if ( bricks[i]->check_impact(ball->get_x(), ball->get_y(), ball->get_vx(), ball->get_vy()) == FROM_DOWN || bricks[i]->check_impact(ball->get_x(), ball->get_y(), ball->get_vx(), ball->get_vy()) == FROM_UP )
		{
			if(bricks[i]->is_bomb())
			{
				ball->reflect_y();
				explosion(bricks[i]->get_top_x(), bricks[i]->get_top_y());
				bomb_explode = true;
			}
			else if(fire && !bomb_explode)
			{
				bricks.erase(bricks.begin() + i);
			}
			else
			{
				ball->reflect_y();
				bricks[i]->affect_impact();
			}
		}
		else if( bricks[i]->check_impact(ball->get_x(), ball->get_y(), ball->get_vx(), ball->get_vy()) == FROM_LEFT || bricks[i]->check_impact(ball->get_x(), ball->get_y(), ball->get_vx(), ball->get_vy()) == FROM_RIGHT)
		{
			if(bricks[i]->is_bomb())
			{
				ball->reflect_x();
				explosion(bricks[i]->get_top_x(), bricks[i]->get_top_y());
				temp_x = bricks[i]->get_top_x();
				temp_y = bricks[i]->get_top_y();
				Brick* red_bomb = new Brick(temp_x, temp_y, 1, 80, 40);
				red_bomb->draw_brick(win, 2);
				win->update_screen();
				Delay(100);
				bomb_explode = true;
			}
			else if(fire && !bomb_explode)
			{
				bricks.erase(bricks.begin() + i);
			}
			else
			{
				ball->reflect_x();
				bricks[i]->affect_impact();
			}
		}
		if(!fire)
			if(bricks[i]->is_ruined())
			{
				temp_x = bricks[i]->get_top_x();
				temp_y = bricks[i]->get_top_y();
				draw_temps(win ,temp_x, temp_y);
				bricks.erase(bricks.begin() + i);
			}
	}
}
void New_game::move(Ball* ball, bool fire, Window* win)
{
	if(ball->get_return() == 1)
		return;
	ball->set_y( ball->get_y() + DT*ball->get_vy());
	ball->set_x( ball->get_x() + DT*ball->get_vx());
	if (ball->get_y() < MIN_Y  )
	{
		ball->reflect_y();
		if(fire)
		{
			fire_return = 1;
			return;
		}
	}
	if(ball->get_x() > MAX_X || ball->get_x() < 0 )
	{
		ball->reflect_x();
		if(fire)
		{
			fire_return = 1;
			return;
		}
	}
	get_life_ball(ball);

	get_fire_ball(ball);

	brick_break(ball, fire, win);

	if(ball->get_y() > MAX_Y)
	{
		if(!first_return)
		{
			first_return = 1;
			x = ball->get_x();
			y = ball->get_y();
		}
		ball->set_return(1);
	}
}
bool New_game::balls_returned()
{
	for(int i =0 ;i < balls.size(); i++)
	{
		if(balls[i]->get_return() == 0)
			return 0;
	}
	return 1;
}
void New_game::update_event(Window* win)
{
	double Angle;
	event = win->pollForEvent();
	if(event.type() == QUIT)
	{
		game_status = 3;
		exit = 1;
	}
	if(event.type() == LCLICK)
		click = 1;
	if(event.type() == LRELEASE)
	{
		space_pressed = 1;
		click = 0;
	}
	if(click == 1)
	{
		if(event.mouseX() != -1)
			mouse_x = event.mouseX();
		if(event.mouseY() != -1)
			mouse_y = event.mouseY();
		if(mouse_x != x)
		{
			Angle = ( atan2((mouse_y - y),(mouse_x - x)) * 180 / PI);
		}
		if(Angle < 0)
			angle = Angle + 180;
		else
			angle = Angle;
		if(angle < MIN_ANGLE)
			angle = MIN_ANGLE;
		if(angle > MAX_ANGLE)
			angle = MAX_ANGLE;
	}
	if(event.type() == KEY_PRESS)
	{
		if(event.pressedKey() == char(LEFT_ARROW))
		{
			if(angle > MIN_ANGLE)
				angle --;
		}
		if(event.pressedKey() == char(RIGHT_ARROW))
		{
			if(angle < MAX_ANGLE)
				angle ++;
		}
		if(event.pressedKey() == char(SPACE_KEY))
			space_pressed = 1;
		if(event.pressedKey() == char(ESC_KEY))
		{
			game_over = 1;
		}
	}
}
void New_game::get_angle_step(Window* win, User* looser)
{
	string ball_nums;
	ball_nums = to_string(balls.size());
	while(!space_pressed)
		{
			cerr << "PINKY";
			update_event(win);
			if(exit)
				break;
			win->clear();
			win->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
			win->show_text("username :  " + looser->get_name(), TEXT_X, TEXT_Y, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("highscore : " + to_string(looser->get_highscore()), TEXT_X, TEXT_Y + TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("Score : " + to_string(looser->get_score()), TEXT_X, TEXT_Y + 2* TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->draw_line(TOP_LINE_X, TOP_LINE_Y, WINDOW_WIDTH, TOP_LINE_Y, BLACK);
			win->draw_line(TOP_LINE_X, BOTTOM_LINE_Y, WINDOW_WIDTH, BOTTOM_LINE_Y, BLACK);
			for(int i = 0 ;i < bricks.size(); i++ )
				bricks[i]->draw_brick(win);
			for(int i = 0;i < life_balls.size(); i++)
				life_balls[i]->draw_life_ball(win);
			for(int i = 0;i < fire_balls.size(); i++)
				fire_balls[i]->draw_fire_ball(win);
			if(!game_over)
			{
				win->draw_png("arrow.png",x - ARROW_CH_BASE_X, y - ARROW_CH_BASE_Y, ARROW_DIM, ARROW_DIM, angle-ANGLE_CH_BASE);
				if(fire_ball)
					win->draw_png("fireBall.png", x, y, 2*FIRE_BALL_R, 2*FIRE_BALL_R);
				else
					win->draw_png("ball.png", x, y, 2*BALL_R, 2*BALL_R);
				win->show_text(ball_nums, x , y + BALLS_TEXT_WIDTH, RED, FONT, TEXT_FONT_SIZE);
				win->draw_png("cross.png", x + CROSS_CH_BASE_X, y + CROSS_CH_BASE_Y, CROSS_DIM, CROSS_DIM);
			}
			win->update_screen();
			if(game_over)
			{
				Delay(1000);
				break;
			}
			Delay(DELAY_TIME);
		}
	space_pressed = 0;
}
void New_game::set_base_state()
{
	first_return = 0;
	for(int i = 0;i < balls.size(); i++)
	{
		balls[i]->set_x(x);
		balls[i]->set_y(y);
		balls[i]->set_angle(angle);
		balls[i]->set_return(0);
	}
}
void New_game::game_flow(Window* win, User* looser)
{
	fire_return = 0;
	Ball* ball = new Ball(x, y);
	ball->set_angle(angle);
	bool on_fire = true;
	int num = 0;
	int check_fire = 0;
	if(double_fire && fire_ball)
		check_fire = 1;
	while(!balls_returned() && ball->get_return() == 0)
		{
			win->clear();
			win->fill_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
			win->show_text("username :  " + looser->get_name(), TEXT_X, TEXT_Y, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("highscore : " + to_string(looser->get_highscore()), TEXT_X, TEXT_Y + TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->show_text("Score : " + to_string(looser->get_score()), TEXT_X, TEXT_Y + 2* TEXT_HEIGHT, BLACK, FONT, TEXT_FONT_SIZE);
			win->draw_line(TOP_LINE_X, TOP_LINE_Y, WINDOW_WIDTH, TOP_LINE_Y, BLACK);
			win->draw_line(TOP_LINE_X, BOTTOM_LINE_Y, WINDOW_WIDTH, BOTTOM_LINE_Y, BLACK);
			for(int i = 0 ;i < bricks.size(); i++ )
				bricks[i]->draw_brick(win);
			for(int i = 0;i < life_balls.size(); i++)
				if((life_balls[i]->get_y() - LIFE_BALL_BASE_Y)/LIFE_BALL_HEIGHT != MAX_ROW)
					life_balls[i]->draw_life_ball(win);
			for(int i = 0;i < fire_balls.size(); i++)
				if((fire_balls[i]->get_y() - FIRE_BALL_BASE_Y)/FIRE_BALL_HEIGHT != MAX_ROW)
					fire_balls[i]->draw_fire_ball(win);
			if(!fire_ball || !on_fire)
			{
				on_fire = false;
				for(int i = 0;i < num/DX +1; i++)
					if(i < balls.size() && balls[i]->get_return() == 0)
					{
						win->draw_png("ball.png", balls[i]->get_x(), balls[i]->get_y(), 2*BALL_R, 2*BALL_R);
					}
				for(int i =0;i < num/DX +1 ; i++)
				{
					if(i < balls.size())
					{
						move(balls[i], 0, win);
					}
				}
			}
			else if(fire_ball && on_fire)
			{
				win->draw_png("fireBall.png", ball->get_x(), ball->get_y(), 2*FIRE_BALL_R, 2*FIRE_BALL_R);
				move(ball, 1, win);
				if(fire_return)
					break;
			}
			win->update_screen();
			num ++;
			Delay(DELAY_TIME);
		}
		if(check_fire)
		{
			double_fire = 0;
			fire_ball = 0;
		}
		if(fire_ball && on_fire)
			fire_ball = false;
		if(double_fire)
			fire_ball = true;
}
void New_game::check_game_over()
{
	for(int i = 0;i < bricks.size() ;i++)
	{
		if(bricks[i]->get_row() >= MAX_ROW)
			game_over = true;
	}
	for(int i = 0;i < life_balls.size() ; i++)
	{
		if(life_balls[i]->get_y() >= MAX_ROW)
			game_over = true;
	}
	for(int i = 0;i < fire_balls.size() ; i++)
	{
		if(fire_balls[i]->get_y() >= MAX_ROW)
			game_over = true;
	}
}
double New_game::get_distance(double x, double y, double X, double Y)
{
	return sqrt((x-X)*(x-X) + (y-Y)*(y-Y));
}
void New_game::get_life_ball(Ball* ball)
{
	for(int i = 0;i < life_balls.size() ; i++)
	{
		double distance = get_distance(ball->get_x(), ball->get_y(),life_balls[i]->get_x(), life_balls[i]->get_y());
		int sum_of_radius = BALL_R + LIFE_BALL_R;
		if(distance <= sum_of_radius)
		{
			life_balls.erase(life_balls.begin() + i);
			num_of_balls++;
		}
	}
}
void New_game::get_fire_ball(Ball* ball)
{
	for(int i = 0;i < fire_balls.size() ; i++)
	{
		double distance = get_distance(ball->get_x(), ball->get_y(),fire_balls[i]->get_x(), fire_balls[i]->get_y());
		int sum_of_radius = BALL_R + FIRE_BALL_R;
		if(distance <= sum_of_radius)
		{
			fire_balls.erase(fire_balls.begin() + i);
			if(fire_ball)
				double_fire = 1;
			fire_ball = true;
		}
	}
}
void New_game::spawn_objects()
{
	int x_chance;
	int things_chance;
	int num = 0;
	Life_ball* life;
	Fire_ball* fire;
	Brick* brick;
	x_chance = rand()%5;
	things_chance = rand()%100;
	if(things_chance < 10)
	{
		num = 0;
		while( num != 1)
		{
			x_chance = rand()%5;
			brick = new Brick(BRICK_BASE_X + x_chance*BRICK_WIDTH, BRICK_BASE_Y, level);
			brick->set_bomb();
			if(!check_full(x_chance, 0))
			{
				num++;
				bricks.push_back(brick);
			}
		}
	}
	else if(things_chance > 10 && things_chance < 40)
	{
		num = 0;
		while(num != 1)
		{
			x_chance = rand()%5;
			life = new Life_ball(LIFE_BALL_BASE_X + x_chance*LIFE_BALL_WIDTH, LIFE_BALL_BASE_Y);
			if(!check_full(x_chance, 0))
			{
				num++;
				life_balls.push_back(life);
			}
		}
	}
	else if(things_chance > 40 && things_chance < 50)
	{
		num = 0;
		while(num != 1)
		{
			x_chance = rand()%5;
			fire = new Fire_ball(FIRE_BALL_BASE_X + x_chance*FIRE_BALL_WIDTH, FIRE_BALL_BASE_Y);
			if(!check_full(x_chance, 0))
			{
				num++;
				fire_balls.push_back(fire);
			}
		}
	}
}
void New_game::spawn_bricks()
{
	Brick* brick;
	srand(time(NULL));
	int x_chance;
	int things_chance;
	int num = 0;
	if(level%5 >= 0 && level%5 < 3)
	{
		while(num != 2)
		{
			x_chance = rand()%5;
			brick = new Brick(BRICK_BASE_X + x_chance*BRICK_WIDTH, BRICK_BASE_Y, level);
			if(!check_full(x_chance, 0))
			{
				num++;
				bricks.push_back(brick);
			}
		}
	}
	else if(level%5 == 3)
	{
		num = 0;
		while(num != 1)
		{
			x_chance = rand()%5;
			brick = new Brick(BRICK_BASE_X + x_chance*BRICK_WIDTH, BRICK_BASE_Y, level);
			if(!check_full(x_chance, 0))
			{
				num++;
				bricks.push_back(brick);
			}
		}
	}
	else
	{
		num = 0;
		while(num != 4)
		{
			x_chance = rand()%5;
			brick = new Brick(BRICK_BASE_X + x_chance*BRICK_WIDTH, BRICK_BASE_Y, level);
			if(!check_full(x_chance, 0))
			{
				num++;
				bricks.push_back(brick);
			}
		}
	}
}

bool New_game::check_full(int x_index, int y_index)
{
	if(has_brick(x_index, y_index) || has_life_ball(x_index, y_index) || has_fire_ball(x_index, y_index))
		return 1;
	return 0;
}
bool New_game::has_brick(int x_index, int y_index)
{
	for(int i = 0;i < bricks.size(); i++)
		if((bricks[i]->get_top_x() - BRICK_BASE_X)/BRICK_WIDTH == x_index && (bricks[i]->get_top_y() - BRICK_BASE_Y)/BRICK_HEIGHT == y_index)
			return 1;
	return 0;
}

bool New_game::has_life_ball(int x_index, int y_index)
{
	for(int i = 0;i < life_balls.size(); i++)
		if((life_balls[i]->get_x() - LIFE_BALL_BASE_X)/LIFE_BALL_WIDTH == x_index && (life_balls[i]->get_y() - LIFE_BALL_BASE_Y)/LIFE_BALL_HEIGHT == y_index)
			return 1;
	return 0;
}
bool New_game::has_fire_ball(int x_index, int y_index)
{
	for(int i = 0;i < fire_balls.size(); i++)
		if((fire_balls[i]->get_x() - FIRE_BALL_BASE_X)/FIRE_BALL_WIDTH == x_index && (fire_balls[i]->get_y() - FIRE_BALL_BASE_Y)/FIRE_BALL_HEIGHT == y_index)
			return 1;
	return 0;
}
