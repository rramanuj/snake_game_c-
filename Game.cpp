#include "Game.h"
#include <iostream>		//for output and input
#include <string>		//for string
#include <sstream>		//for streamstring
#include <fstream> //
using namespace std;

void Game::set_up(UserInterface* pui) {
	int answer;
	//prepare game
	//set up the holes

	//mouse state already set up in its contructor
	//set up snake


	ostringstream os;
		os << "PRESS 1 FOR NEW GAME, OR 2 TO CONTINUE!";
		cin >> answer;
		if (answer == 1) {
			snake_.position_at_random();
		}
		else {
			loadGame(*this);
		}
	snake_.spot_mouse(&mouse_);
	//set up the UserInterface
	p_ui = pui;
}
void Game::run() {
	assert(p_ui != nullptr);
	p_ui->draw_grid_on_screen(prepare_grid());
	key_ = p_ui->get_keypress_from_user();
	while (!has_ended(key_))
	{
		if (is_arrow_key_code(key_))
		{
			mouse_.scamper(key_);
			snake_.chase_mouse();
			p_ui->draw_grid_on_screen(prepare_grid());
			apply_rules();
		}
		key_ = p_ui->get_keypress_from_user();
	}
	p_ui->show_results_on_screen(prepare_end_message());
}
string Game::prepare_grid() {
	//prepare a string that holds the grid information
	ostringstream os;
	for (int row(1); row <= SIZE; ++row)	//for each row (vertically)
	{
		for (int col(1); col <= SIZE; ++col)	//for each column (horizontally)
		{
			if ((row == snake_.getY()) && (col == snake_.getX()))
				os << snake_.symbol_;	//show snake
			else
				if ((row == mouse_.get_y()) && (col == mouse_.get_x()))
					os << mouse_.get_symbol();	//show mouse
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
	if (snake_.has_caught_mouse())
		mouse_.die();
	else
		if (mouse_.has_reached_a_hole(underground_))
			mouse_.escape_into_hole();
}
bool Game::has_ended(char key) {
	return ((key == 'Q') || (!mouse_.is_alive()) || (mouse_.has_escaped()));
}


void Game::setSnaketoLoad(int x, int y) {
	snake_.set_position(x,y);
};

const int Game::getSnakeX() {
	return snake_.getX();
}

const int Game::getSnakeY() {
	return snake_.getY();
}


string Game::prepare_end_message() {
	ostringstream os;
	if (mouse_.has_escaped())
		os << "\n\nEND OF GAME: THE MOUSE ESCAPED UNDERGROUND!";
	else
		if (!mouse_.is_alive())
			os << "\n\nEND OF GAME: THE SNAKE ATE THE MOUSE!";
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
	os << aGame.getSnakeY() << "\n";

	return os;
}
const istream& operator>>(istream& is,  Game &aGame) {
	ostringstream os;
	int x;
	int y;
	is >> x;
	is >> y;
	aGame.setSnaketoLoad(x, y);
	return is;
}