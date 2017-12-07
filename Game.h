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
	//friend ofstream& operator <<(ofstream& fout, const string& game_);	//serilization
	//friend ifstream& operator >>(ifstream& fin, const string& game_);
	//functions to put data into and get data from streams

	ostream& putDataInStream(ostream& os) const;
	ostream& putGameDataInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	istream& getGameDataInStream(istream& is);
	void readLastGameStatus(const string& fileName);
	void storeGameStatus(const string& fileName) const;

	//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

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

ostream& operator<<(ostream&, const string& game_);	//output operator
istream& operator>>(istream&, const string& game_);	    //input operator

