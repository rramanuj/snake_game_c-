#pragma once
#include "GridItem.h"
class FixedGridItem : public GridItem {
public:
	FixedGridItem(const char& symbol, const int& x, const int& y);
	int get_x() const;
	int get_y() const;
	bool is_at_position(const int& x, const int& y) const;
private:
	const int x, y;
};
