#pragma once
class Hole {
public:
	//constructors
	Hole();
	const Hole(int x, int y);
	//assessors
	int get_x() const;
	int get_y() const;
	char get_symbol() const;
	bool is_at_position(int x, int y);
private:

	static const int MAXHOLES; //number of holes in underground
							   //data members
	char symbol_;
	int x_, y_;
};