#include "Game.h"
#include <iostream>		//for output and input
#include <string>		//for string
#include <sstream>		//for streamstring
#include <fstream> //
using namespace std;

void Game::set_up(UserInterface* pui) {
	//prepare game
	//set up the holes
	/*underground_.set_hole_no_at_position(0,  4,  3);
	underground_.set_hole_no_at_position(1, 15, 10);
	underground_.set_hole_no_at_position(2,  7, 15);*/
	//mouse state already set up in its contructor
	//set up snake
	snake_.position_at_random();
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


string Game::prepare_end_message() {
	ostringstream os;
	if (mouse_.has_escaped())
		os << "\n\nEND OF GAME: THE MOUSE ESCAPED UNDERGROUND!";
	else
		if (!mouse_.is_alive())
			os << "\n\nEND OF GAME: THE SNAKE ATE THE MOUSE!";
		else
			os << "\n\nEND OF GAME: THE PLAYER ENDED THE GAME!";
	return os.str();

	

	
}

//serialization - replaces the use of the operator functions

/*ofstream& operator <<(ofstream& fout, const string& game) {
	
	fout.open("Game.txt", ios::out);
	if (fout.fail())
		cout << "\nAn error has occurred when opening the file.";
	else
		fout << game;
	fout.close();
	return(fout);
}

ifstream& operator >>(ifstream& fin, const string& game) {
	fin.open("Game.txt", ios::in);
	if (fin.fail())
		cout << "\nAn error has occurred when opening the file.";
	else
		fin >> game;
	fin.close();
	return(fin);
}*/
void Game::storeGameStatus(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& Game::putDataInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	putGameDataInStream(os);			//put bank account core information in stream
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions, one per line
	return os;
}
ostream& Game::putGameDataInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountType_ << "\n";				//put account type
	os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& Game::getDataFromStream(istream& is) {
	//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	is >> transactions_;					//get all transactions (if any)
	return is;
}
istream& Game::getGameDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountType_;						//get account type
	is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
	//put (unformatted) BankAccount details in stream
	return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
	//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}