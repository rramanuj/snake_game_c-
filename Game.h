#pragma once
#include "Snake.h"
#include "Mouse.h"
#include "Underground.h"
#include "UserInterface.h"

class Game
{
public:
	
	void set_up(UserInterface* pui);
	void run();
	string prepare_grid();
	bool is_arrow_key_code(int keycode);
	void apply_rules();
	int find_hole_number_at_position(int x, int y);
	bool has_ended(char key);
	string prepare_end_message();
	friend ofstream& operator <<(ofstream& fout, const string& game_);	//serilization
	friend ifstream& operator >>(ifstream& fin, const string& game_);
private:
	Mouse mouse_;
	Snake snake_;
	Underground underground_;
	UserInterface* p_ui;
	int key_;
};
