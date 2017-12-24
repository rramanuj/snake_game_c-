// Underground.cpp: implementation of the Underground class 
//////////////////////////////////////////////////////////////////////

#include "Underground.h"

//////////////////////////////////////////////////////////////////////


static const int MAXHOLES(3); //number of holes in underground
const Hole h(4, 3);
const Hole h2(15, 10);
const Hole h3(7, 15);

Underground::Underground() : holes_{h,h2,h3}
{	
	
}
Hole Underground::get_hole_no(int no) const {
	assert (is_valid_hole_number(no));	//precondition: valid hole number
	return holes_.at(no);
}
/*void Underground::set_hole_no_at_position(int no, int x, int y) {
	assert (is_valid_hole_number(no));	//precondition: valid hole number
	Hole h(4, 2)
		switch (no) {
		case 0: holes_.at(0) = h; break;
		case 1: holes_.at(1) = h; break;
		case 2: holes_.at(2) = h; break;
		}*/
bool Underground::overlaps(int x, int y) const {
	if (h.get_x() == x && h.get_y() == y) {
		return true;
	}
	if (h2.get_x() == x && h2.get_y() == y) {
		return true;
	}
	if (h3.get_x() == x && h3.get_y() == y) {
		return true;
	}
	else return false;
}

bool Underground::is_valid_hole_number(int no) const {
	return (no >= 0) && (no < holes_.size()); 
}
