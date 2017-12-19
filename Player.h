#pragma once
#include <iostream>		//for output and input
#include <string>		//for string
#include "Score.h"
#include "UserInterface.h"
using namespace std;
class Player {
public:
	Player();
	string get_name() const;
	int get_score_amount() const;
	void update_score_amount(int);
	void set_name(string name);
private:
	string name_;
	Score score_;
};
