#include "Game.h"
#include <iostream>		//for output and input
#include <string>		//for string
#include <sstream>		//for streamstring
#include <fstream> //
using namespace std;


void Game::set_up(UserInterface* pui, Player& player, bool savedGame) {
	int answer;
	string name;

	player_ = &player;	//if its a saved game it sets the parameters to whatever is on the thing
	if (savedGame) {
		loadGame();
	}

	snake_.spot_mouse(&mouse_);
	//set up the UserInterface
	p_ui = pui;
	
	
}
void Game::run() {
		assert(p_ui != nullptr);
	
		bool cheatmode = false;
		while (check_for_overlaps())
		{
			snake_.position_at_random();
			mouse_.position_at_random();
			nut_.position_at_random();
		}
		p_ui->draw_grid_on_screen(prepare_grid());
		p_ui->show_results_on_screen(display_score_bar());
		key_ = p_ui->get_keypress_from_user();
		while (!has_ended(key_))
		{

			if (is_arrow_key_code(key_))
			{
				last_snake_x = snake_.get_x();
				last_snake_y = snake_.get_y();
				last_nut_status = nut_.has_been_collected();
				last_mouse_x = mouse_.get_x();
				last_mouse_y = mouse_.get_y();
				mouse_.scamper(key_);
				if (!cheatmode)
				{
					snake_.chase_mouse();	//only chase mouse is cheatmode is off.
				}
				p_ui->draw_grid_on_screen(prepare_grid());
				apply_rules();
				p_ui->show_results_on_screen(display_score_bar());
				if (cheatmode)
				{
					p_ui->show_results_on_screen("\nCHEAT MODE ACTIVATED!");
				}
			}
			if (key_ == 83) {
				storeGameStatus(*this); //saves game status
				p_ui->draw_grid_on_screen(prepare_grid());
				apply_rules();
				p_ui->show_results_on_screen(display_score_bar());
				p_ui->show_results_on_screen("\nGame has been saved!");

			}
			
			if (key_ == 76) {
				this->loadGame(); //Loads previous save
				p_ui->draw_grid_on_screen(prepare_grid());
				apply_rules();
				p_ui->show_results_on_screen(display_score_bar());
				p_ui->show_results_on_screen("\nPrevious Save Loaded!");

			}	
			if (key_ == 85) { //undo
				if (last_snake_x == 0) 
				{
					p_ui->show_results_on_screen("\nNo move to undo!");
				}
				else {
					mouse_.reset_position(last_mouse_x, last_mouse_y);
					snake_.reset_position(last_snake_x, last_snake_y);
					snake_.set_tail(last_snake_x, last_snake_y);
					//nut to do
					if (!last_nut_status) { //if nut hasn't been collected reset nut pos
						nut_.new_game();
					}

					p_ui->draw_grid_on_screen(prepare_grid());
					apply_rules();
					p_ui->show_results_on_screen(display_score_bar());
					p_ui->show_results_on_screen("\nLast Move Undone!!");
				}

			}
			if (key_ == 67) {		//cheat mode
				if (cheatmode) 
				{
					cheatmode = false;
					p_ui->show_results_on_screen("\nCHEAT MODE DEACTIVATED!");
				}
				else {
					cheatmode = true;
					p_ui->show_results_on_screen("\nCHEAT MODE ACTIVATED!");
				}
			

			}
			key_ = p_ui->get_keypress_from_user();
		}
		p_ui->show_results_on_screen(prepare_end_message());
		new_game();
}
void Game::new_game() {
	
}
string Game::display_score_bar()const {
	ostringstream os;
	os << "NAME: " << player_->get_name() << "\tSCORE: " << player_->get_score_amount();
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
bool Game::check_for_overlaps() {
	if (nut_.get_y() && nut_.get_x() == mouse_.get_x() && mouse_.get_y())
		return true;
	else if (nut_.get_y() && nut_.get_x() == snake_.get_x() && snake_.get_y())
		return true;
	else if (snake_.get_y() && snake_.get_x() == mouse_.get_x() && mouse_.get_y())
		return true;

	//check if instances are on the holes
	else if (underground_.overlaps(mouse_.get_x(), mouse_.get_y()))
		return true;
	else if (underground_.overlaps(nut_.get_x(), nut_.get_y()))
		return true;
	else if (underground_.overlaps(snake_.get_x(), snake_.get_y()))
		return true;
	else
		return false;
	}
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
			player_->update_score_amount(-1);
			mouse_.die();
		}
		else if (mouse_.has_reached_a_hole(underground_) && (nut_.has_been_collected())) {
			player_->update_score_amount(1);
			mouse_.escape_into_hole();
		}
		else //else if mouse has reached a hole without the collection of a nut..
			if (mouse_.has_reached_a_hole(underground_) && (!nut_.has_been_collected())) {
				int hole, new_x, new_y, randomNumber;
				for (int h_no(0); h_no < underground_.holes_.size(); ++h_no) {
					if ((underground_.get_hole_no(h_no).get_x() == (mouse_.get_x())) && ((underground_.get_hole_no(h_no).get_y()) == mouse_.get_y()))
					{	
						//this for loop is finding which hole the mouse is on top of by getting the x & y coordinates of each hole and 
						//comparing it to the x & y co-ordinates of the mouse
						hole = (h_no);	//sets the hole variable to the hole number the mouse is on top of when found
					}
				}
				randomNumber = rand() % 3;	//generates a random number between 1 - 3
				while (randomNumber == hole) {	//if the random number is the same as hole the entry hole, reset random number
					randomNumber = rand() % 3;	
				}
				//randomly sets the mouse x & y co-ordinates to another hole position, excluding the entry hole.
				new_x = underground_.get_hole_no(randomNumber).get_x();
				new_y = underground_.get_hole_no(randomNumber).get_y();
				mouse_.reset_position(new_x, new_y);
			}
}
	

bool Game::has_ended(char key) {
	return ((key == 'Q') || (!mouse_.is_alive()) || (mouse_.has_escaped()));
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
	return os.str();
}


string Game::save_message() {
	ostringstream os;
	return os.str();
}


//serialization - replaces the use of the operator functions


void Game::loadGame() {
	int sx, sy, mx, my, score;
	bool nut;
	string output, name;
	ifstream fromFile;
	fromFile.open("Game.txt", ios::in); 	//open file in read mode
	if (fromFile.fail()) {
		cout << "\nNo game save available.";
	}
	else {
		fromFile >> (*this);  	//read  all info from game with pointer
		fromFile >> sx; //snake x co-ordinates
		fromFile >> sy;	//snake y co-ordinates
		fromFile >> mx;	//mouse x co-ordinates
		fromFile >> my; //mouse y co-ordinates
		fromFile >> nut;	//nut status (has been collected or no)
		fromFile >> score; //player last score
		fromFile >> name;

		mouse_.reset_position(mx, my);
		snake_.reset_position(sx, sy);
		snake_.set_tail(sx, sy);

		if (nut) {
			nut_.disappear();
		}
		player_->set_name(name);
		player_->set_amount(score);
		fromFile.close();			//close file: optional here
	}
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
	os << aGame.snake_.get_x() << "\n";	//saves the snake x position
	os << aGame.snake_.get_y() << "\n";	//snakes the snake y position
	os << aGame.mouse_.get_x() << "\n";	//saves the snake x position
	os << aGame.mouse_.get_y() << "\n";	//snakes the snake y position
	os << aGame.nut_.has_been_collected() << "\n";	//has the nut been collected?
	os << aGame.player_->get_score_amount()<< "\n";	//gets the player score
	os << aGame.player_->get_name() << "\n";	//gets the player name
	return os;
}



const istream& operator>>(istream& is, Game& aGame) {
	ostringstream os;
	return is;
}
