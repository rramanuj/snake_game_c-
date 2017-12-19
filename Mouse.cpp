// Mouse.cpp: implementation of the Mouse class
//////////////////////////////////////////////////////////////////////

#include "Mouse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mouse::Mouse() : MoveableGridItem(MOUSE, 8, 9), alive_(true), escaped_(false),mouse_dx_(0), mouse_dy_(0) {}

//////////////////////////////////////////////////////////////////////
// Public functions
//////////////////////////////////////////////////////////////////////

bool Mouse::is_alive() const {
	return alive_;
}
bool Mouse::has_escaped() const {
	return escaped_;
}
bool Mouse::can_collect_nut(const Nut& n) const {
	if (!(n.has_been_collected()) && (is_at_position(n.get_x(), n.get_y())))
		return true;
	else
		return false;
}
void Mouse::new_game() {
	alive_ = true;
	escaped_ = false;
	position_in_middle_of_grid();
}
bool Mouse::has_reached_a_hole(const Underground& ug) const {	//get functions should be changed to constant
																	//changed function to constant
	for (int h_no(0); h_no < ug.holes_.size(); ++h_no)
	{
		Hole h = ug.get_hole_no(h_no);
		if (is_at_position(h.get_x(), h.get_y()))
			return true;
	}
	return false;
}
void Mouse::die() {
	alive_ = false;
}
void Mouse::escape_into_hole() 
{
	escaped_ = true;
}
void Mouse::scamper(char k) { //move mouse in required direction
  //pre: Key is an arrow representing the direction in which the mouse moves
	//find direction indicated by key
	switch(k)               //...depending on the selected key...
	{
		case LEFT:           //when LEFT arrow pressed...
			mouse_dx_ = -1;    //decrease the X coordinate
			mouse_dy_ = 0;
			break;
		case RIGHT:          //when RIGHT arrow pressed...
			mouse_dx_ = +1;    //increase the X coordinate
			mouse_dy_ = 0;
			break;
		case UP:             //when UP arrow pressed...
			mouse_dx_ = 0;
			mouse_dy_ = -1;    //decrease the Y coordinate
			break;
		case DOWN:           //when DOWN arrow pressed...
			mouse_dx_ = 0;
			mouse_dy_ = +1;    //increase the Y coordinate
			break;
	}
	//update mouse coordinates if move is possible
	if (((get_x() + mouse_dx_) >= 1) && ((get_x() + mouse_dx_) <= SIZE) &&
		 ((get_y() + mouse_dy_) >= 1) && ((get_y() + mouse_dy_) <= SIZE) )
		//switched to getters for encapsulation
	{
		update_position(mouse_dx_, mouse_dy_);		//go in that direction
	}
}

//////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////

void Mouse::position_in_middle_of_grid() {
	reset_position((SIZE / 2), (SIZE / 2)); //sets to mid
}