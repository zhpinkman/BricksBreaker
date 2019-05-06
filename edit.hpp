#ifndef EDIT
#define EDIT EDIT


#include "button.hpp"
#include "rsdl.hpp"
#include "User.hpp"
#include <sstream>

using namespace std;

#define RIGHT_ARROW 79
#define LEFT_ARROW 80
#define DOWN_ARROW 81
#define UP_ARROW 82
#define ENTER_KEY 13
#define ESC_KEY 27
#define SPACE_KEY 32
#define EDIT_TEXT_X 100
#define EDIT_TEXT_Y 80
#define EDIT_TEXT_WIDTH 300
#define EDIT_TEXT_HEIGHT 80
#define SAVE_X 80
#define SAVE_Y 400
#define CANCEL_X 300
#define CANCEL_Y 400
#define EDIT_BUTTON_WIDTH 100
#define EDIT_BUTTON_HEIGHT 60
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 700
#define MAX_LEN 10
#define BACK_SPACE 8
#define EDIT_DELAY_TIME 15
#define BACKGROUND "background.png"

class Edit
{
public:
	bool is_empty();
	Edit(string current_name = "", char c = ' ');
	void edit_menu(Window* win, bool& user_log_in, User* looser);
	void update_event(Window* win);
	void proccess_input();
	void add_char();
	void delete_last_char();
	void initialize();
private:
	int pointer;
	string pre_name;
	string name;
	bool saved;
	bool canceled;
	bool input;
	char last_char;
	bool back_space;
	Event event;
	Button* display;
	Button* save;
	Button* cancel;
	bool quit;
};

#endif
