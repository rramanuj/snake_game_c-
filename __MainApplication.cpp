// Rasesh Ramanuj

//--------------------------------
//include standard libraries
#include <iostream>		//for output and input
#include <string>		//for string
#include <fstream>
#include <sstream>		//for streamstring
using namespace std;

//include class modules
#include "Game.h"

//using OO approach
//---------------------------------
UserInterface ui;
void newGame(bool& SavedGame, Player& player_);
int main()
{

	Player player_;

	int answer;
	string name;
	bool SavedGame = false;
	ui.show_results_on_screen("       ---_ ......._-_--.\n");
	ui.show_results_on_screen("      (| \ /      / /| \  \")\n");
	ui.show_results_on_screen("      /  /     .'  -=-'   `.\n");
	ui.show_results_on_screen("     /  /    .'             )\n");
	ui.show_results_on_screen("   _/  /   .'        _.)   /\n");
	ui.show_results_on_screen("  / o   o        _. - ' /  .'\n");
	ui.show_results_on_screen("  \          _.-'    / .'*|\n");
	ui.show_results_on_screen("   \______.-'//    .'.' \*|\n");
	ui.show_results_on_screen("    \|  \ | //   .'.' _ |*|\n");
	ui.show_results_on_screen("     `   \|//  .'.'_ _ _|*|\n");
	ui.show_results_on_screen("      .  .// .'.' | _ _ \*|\n");
	ui.show_results_on_screen("      \`-|\_/ /    \ _ _ \*\\n");
	ui.show_results_on_screen("       `/'\__/      \ _ _ \*\\n");
	ui.show_results_on_screen("      /^|            \ _ _ \*\n");
	ui.show_results_on_screen("     '  `             \ _ _ \ \n");
	ui.show_results_on_screen("WELCOME TO THE AMAZING SNAKE GAME!\n1. New Game\n2. Load\n");
	cin >> answer;



	if (answer == 1) {
		SavedGame = false;
		newGame(SavedGame, player_);
	}
	else if (answer == 2) {
		ifstream fromFile;
		fromFile.open("Game.txt", ios::in); 	//open file in read mode
		if (fromFile.fail()) {
			ui.show_results_on_screen("No game save available. Starting new game.");
			ui.hold_window();
			SavedGame = false;
			newGame(SavedGame, player_);
		}
		else {
			SavedGame = true;
		}
	}
		do {
			Game game;
			game.set_up(&ui, player_, SavedGame);
			SavedGame = false;
			game.run();
		} while (ui.play_again() == 'Y');
	
		ui.hold_window();
		return 0;
	}

void newGame(bool& SavedGame, Player& player_) {
	string name;
	SavedGame = false;
	ui.show_results_on_screen("\nWHAT IS YOUR NAME?\n");
	cin >> name;
	player_.set_name(name);
	SavedGame = false;
}
void loadGame() {

}