#include "Game.h"
#include <iostream>		//for output and input
#include <string>		//for string
#include <sstream>		//for streamstring
#include <fstream> //
using namespace std;

void Game::set_up(UserInterface* pui) {
	int answer;
	string name;
	//prepare game
	//set up the holes

	//mouse state already set up in its contructor
	//set up snake

	p_ui->show_results_on_screen("WELCOME TO THE AMAZING SNAKE GAME!\n1. New Game\n2. Continue\n");
		cin >> answer;
		if (answer == 1) {
			p_ui->show_results_on_screen("WHAT IS YOUR NAME?\n");
			cin >> name;
			this->player_.set_name(name);
			snake_.new_game();
			nut_.new_game();
		}
		else {
			loadGame(*this);
		}
	snake_.spot_mouse(&mouse_);
	//set up the UserInterface
	p_ui = pui;
}
void Game::run() {
	do {
		assert(p_ui != nullptr);
		p_ui->draw_grid_on_screen(prepare_grid());
		p_ui->show_results_on_screen(display_score_bar());
		key_ = p_ui->get_keypress_from_user();
		while (!has_ended(key_))
		{
			if (is_arrow_key_code(key_))
			{
				mouse_.scamper(key_);
				snake_.chase_mouse();
				p_ui->draw_grid_on_screen(prepare_grid());
				apply_rules();
				p_ui->show_results_on_screen(display_score_bar());

			}
			key_ = p_ui->get_keypress_from_user();
		}
		p_ui->show_results_on_screen(prepare_end_message());
		new_game();
	} while (p_ui->get_keypress_from_user() == 'Y');
}
void Game::new_game() {
	nut_.new_game();
	snake_.new_game();
	mouse_.new_game();

}
string Game::display_score_bar()const {
	ostringstream os;
	os << "NAME: " << player_.get_name() << "\tSCORE: " << player_.get_score_amount();
	return os.str();
}
string Game::prepare_grid() {
	//prepare a string that holds the grid information
	ostringstream os;
	for (int row(1); row <= SIZE; ++row)	//for each row (vertically)
	{
		for (int col(1); col <= SIZE; ++col)	//for each column (horizontally)
		{
			if ((row == snake_.get_y()) && (col == snake_.get_x()))
				os << snake_.get_symbol();	//show snake
			else
				if (snake_.get_tail_position(col, row))
					os << snake_.output_tail();
			else
				if ((row == mouse_.get_y()) && (col == mouse_.get_x()))
					os << mouse_.get_symbol();	//show mouse
				else
					if (((row == nut_.get_y()) && (col == nut_.get_x())) && !nut_.has_been_collected())
						os << nut_.get_symbol(); //show nut
					else
				{
					const int hole_no(find_hole_number_at_position(col, row));
					if (hole_no != -1)
						os << underground_.get_hole_no(hole_no).get_symbol();	//show hole
					else
						os << FREECELL;	//show free grid cell
				}
		} //end of col-loop
		os << endl;
	} //end of row-loop
	return os.str();
} //end prepare_grid

bool Game::is_arrow_key_code(int keycode) {
	return (keycode == LEFT) || (keycode == RIGHT) || (keycode == UP) || (keycode == DOWN);
	}
int Game::find_hole_number_at_position(int x, int y) {
	for (int h_no(0); h_no < underground_.holes_.size(); ++h_no)
		if (underground_.get_hole_no(h_no).is_at_position(x, y))
			return h_no;		//number of the hole
	return -1;				//not a hole
}
void Game::apply_rules() {
	if (mouse_.can_collect_nut(nut_))
		nut_.disappear();
	else
		if (snake_.has_caught_mouse())
		{
			player_.update_score_amount(-1);
			mouse_.die();
		}
		else
			if (mouse_.has_reached_a_hole(underground_) && (nut_.has_been_collected())) {
				player_.update_score_amount(1);
				mouse_.escape_into_hole();
			}
}
bool Game::has_ended(char key) {
	return ((key == 'Q') || (!mouse_.is_alive()) || (mouse_.has_escaped()));
}


void Game::SetToSerializedData(int sx, int sy, int mx, int my, int score, string name) {
	snake_.set_position(sx,sy);	//need to ammend for serialization.
//	mouse_.reset_position(mx, my);		//commented about there is no point in storing this if the mouse will die..
	player_.set_name(name);
	player_.update_score_amount(score);
};

const int Game::getSnakeX() {
	return snake_.get_x();
}

const int Game::getSnakeY() {
	return snake_.get_y();
}

const int Game::getMouseX() {
	return mouse_.get_x();
}

const int Game::getMouseY() {
	return mouse_.get_y();
}
const string Game::get_player_name() {
	return player_.get_name();
}

const int Game::get_player_score() {
	return player_.get_score_amount();
}


string Game::prepare_end_message() {
	ostringstream os;
	if (mouse_.has_escaped())
		os << "\n\nEND OF GAME: THE MOUSE ESCAPED UNDERGROUND!\nPLAY AGAIN? Y/N";
	else
		if (!mouse_.is_alive())
			os << "\n\nEND OF GAME: THE SNAKE ATE THE MOUSE!\nPLAY AGAIN? Y/N";
		else
			os << "\n\nEND OF GAME: THE PLAYER ENDED THE GAME!";
	storeGameStatus(*this); //saves game status
	return os.str();
	
}


//serialization - replaces the use of the operator functions


void Game::loadGame(Game& game) {
	ifstream fromFile;
	fromFile.open("Game.txt", ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		fromFile >> (game);  	//read  all info from game with pointer
		fromFile.close();			//close file: optional here
}

void Game::storeGameStatus( Game game)  {
	ofstream fout;
	fout.open("Game.txt", ios::out);
	if (fout.fail())
		cout << "\nAn error has occurred when opening the file.";
	else
		fout << game;	//insertion operator<< for Game instances
	fout.close();
}

const ostream& operator<<(ostream& os, Game& aGame)  {
	
	os << aGame.getSnakeX() << "\n";	//saves the snake x position
	os << aGame.getSnakeY() << "\n";	//snakes the snake y position
	os << aGame.getMouseX() << "\n";	//saves the snake x position
	os << aGame.getMouseY() << "\n";	//snakes the snake y position
	os << aGame.get_player_score() << "\n";	//gets the player score
	os << aGame.get_player_name() << "\n";	//gets the player name

	return os;
}
const istream& operator>>(istream& is,  Game &aGame) {
	ostringstream os;
	int sx,sy,mx,my,score;
	string name;
	is >> sx; //snake x co-ordinates
	is >> sy;	//snake y co-ordinates
	is >> mx;	//mouse x co-ordinates
	is >> my; //mouse y co-ordinates
	is >> score; //player last score
	is >> name;	//player last name
	aGame.SetToSerializedData(sx, sy,mx,my,score,name);
	
	return is;
}
