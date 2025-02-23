#include "MoveableGridItem.h"
MoveableGridItem::MoveableGridItem(const char& symbol, const int& x, const int& y) : GridItem(symbol), x_(x), y_(y) {}
int MoveableGridItem::get_x() const {
	return x_;
}
const static RandomNumberGenerator rng_;
int MoveableGridItem::get_y() const {
	return y_;
}
bool MoveableGridItem::is_at_position(const int& x, const int& y) const {
	return (x_ == x) && (y_ == y);
}
void MoveableGridItem::reset_position(const int& x, const int& y) {
	x_ = x;
	y_ = y;
}
void MoveableGridItem::update_position(const int& dx, const int& dy) {
	x_ += dx;
	y_ += dy;
}