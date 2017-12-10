#include "MoveableGridItem.h"
MoveableGridItem::MoveableGridItem(const char& symbol, const int& x, const int& y) : GridItem(symbol), x(x), y(y) {}
int MoveableGridItem::get_x() const {
	return x;
}
int MoveableGridItem::get_y() const {
	return y;
}
bool MoveableGridItem::is_at_position(const int& x_, const int& y_) const {
	return (x == x_) && (y == y_);
}
void MoveableGridItem::reset_position(const int& x_, const int& y_){
	x = x_;
	y = y_;
}
void MoveableGridItem::update_position(const int& dx, const int& dy){
	x += dx;
	y += dy;
}