#pragma once
#include "GridItem.h"
class MoveableGridItem :
	public GridItem
{
public:
	MoveableGridItem(const char& symbol, const int& x, const int& y);
	~MoveableGridItem();
	int get_x() const;
	int get_y() const;
	bool is_at_position(const int& x, const int& y) const;
	void reset_position(const int& x, const int& y);
	void update_position(const int& dx, const int& dy);
private:
	int x, y;
};

