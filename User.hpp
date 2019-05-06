#ifndef USER
#define USER USER

using namespace std;

#include <string>

class User
{
public:
	User(string user_name = " ", int recent_score = 0)
	:score(recent_score), name(user_name), high_score(0)
	{}
	string get_name() { return name; }
	void set_name(string new_name) { name = new_name; }
	int get_score() { return score; }
	int get_highscore() { return high_score; }
	void set_highscore(int high) { high_score = high; }
	void set_score(int new_score ) 
	{
		score = new_score; 
		if(score > high_score)
			high_score = score;
	}
private:
	int score;
	int high_score;
	string name;
};


#endif