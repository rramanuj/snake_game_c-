#pragma once
#include "Snake.h"
#include "Mouse.h"
#include "Underground.h"
#include "UserInterface.h"
#include "Player.h"
class Game
{
public:
	
	void set_up(UserInterface* pui);
	void run();
	void new_game();
	string display_score_bar() const;

	string prepare_grid();
	bool is_arrow_key_code(int keycode);
	void apply_rules();
	int find_hole_number_at_position(int x, int y);
	bool has_ended(char key);
	string prepare_end_message();
	void loadGame(Game &game);
	void storeGameStatus(Game game);
	 
	//functions to put data into and get data from streams

	void SetToSerializedData(int sx, int sy, int mx, int my, int score, string name);


	//void loadGame(Game &game) const;
	//void storeGameStatus(Game game) const;
	const int getSnakeX();
	const int getSnakeY();
	const int getMouseX();
	const int getMouseY();
	const string get_player_name();
	const int get_player_score();
	

private:
	Mouse mouse_;
	Snake snake_;
	Underground underground_;
	UserInterface* p_ui;
	int key_;
	Nut nut_;
	Player player_;
	/*string game_status; 
	string name()const;	//starts when the game instance is created.*/
	

};
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

const ostream& operator<<(ostream&, Game &game_) ;	//output operator
const istream& operator>>(istream&, Game &game_) ;	    //input operator

