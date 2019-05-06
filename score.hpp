#include "rsdl.hpp"
#include "User.hpp"
#include "button.hpp"
#include <vector>
#include <algorithm>

using namespace std;

#define ENTER_KEY 13
#define ESC_KEY 27
#define SCORE_WINDOW_WIDTH 500
#define SCORE_WINDOW_HEIGHT 700
#define SCORE_BOARD_FONT "records.ttf"
#define SCORE_BOARD_FONT_SIZE 90
#define BASE_X 30
#define BASE_Y 100
#define SCORE_BASE_X 400
#define BACK_BUTTON_X 200
#define BACK_BUTTON_Y 600
#define BACK_BUTTON_WIDTH 100
#define BACK_BUTTON_HEIGHT 60
#define HEIGHT_DIFF	100
#define SCORE_DELAY_TIME 25

class Score_board
{
public:
	Score_board();
	void Sort();
	void update_event(Window* win);
	void draw_scoreboard(Window* win);
	void add_user(User* new_user);
	User* find_history(User* new_user);
	vector<User*> get_users() { return users; }
private:
	Event event;
	bool exit;
	vector<User*> users;
	Button* back;
};
