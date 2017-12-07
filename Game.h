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
	void loadGame(Game &game);
	void storeGameStatus(Game game);
	//friend ofstream& operator <<(ofstream& fout, const string& game_);	//serilization
	//friend ifstream& operator >>(ifstream& fin, const string& game_);
	//functions to put data into and get data from streams

	//void loadGame(Game &game) const;
	//void storeGameStatus(Game game) const;
	const int getSnakeX();
	const int getSnakeY();
	void setSnaketoLoad(int x, int y);
	

private:
	Mouse mouse_;
	Snake snake_;
	Underground underground_;
	UserInterface* p_ui;
	int key_;
};
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

const ostream& operator<<(ostream&, Game &game_) ;	//output operator
const istream& operator>>(istream&, Game &game_) ;	    //input operator

