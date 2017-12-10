#include "FixedGridItem.h"
FixedGridItem::FixedGridItem(const char& symbol, const int& x, const int& y) : GridItem(symbol), x_(x), y_(y) {}
int FixedGridItem::get_x() const {
	return x;
}
int FixedGridItem::get_y() const {
	return y;
}
bool FixedGridItem::is_at_position(const int& x, const int& y) const {
	return (x == x) && (y == y);
}