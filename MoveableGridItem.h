#pragma once
#include "GridItem.h"
class MoveableGridItem :
	public GridItem
{
public:
	MoveableGridItem(const char& symbol, const int& x, const int& y);
	int get_x() const;
	int get_y() const;
	bool is_at_position(const int& x, const int& y) const;
	void reset_position(const int& x, const int& y);
	void update_position(const int& dx, const int& dy);
	//void new_game();		//to reset the positions of the snake and mouse when a new game is called?
private:
	int x_, y_;
};

