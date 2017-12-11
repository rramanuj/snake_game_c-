// Snake.cpp: implementation of the Snake class
////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////
#include "constants.h"
#include "Mouse.h"
#include "Snake.h"

Snake::Snake() : MoveableGridItem(SNAKEHEAD, rng_.get_random_value(SIZE), rng_.get_random_value(SIZE)) {
	p_mouse_ = nullptr; //to make the pointer is safe before the snake spots the mouse
	for (int i = 0; i < 3; i++) {
		tail.push_back(Tail(get_x(), get_y()));
	}
}
Snake::~Snake()
{}
bool Snake::has_caught_mouse() {
	return is_at_position(p_mouse_->get_x(), p_mouse_->get_y());
	//encapsulation again, replaced with getters
}

void Snake::new_game() {
	//reset the snakes position for a new game 
	position_at_random();
}
char Snake::output_tail() const
{
	for (unsigned int i = 0; i < tail.size(); i++)
	{
		return tail[i].get_symbol();
	}
}
void Snake::spot_mouse(Mouse* p_mouse) {
	assert(p_mouse != nullptr);	 //Pre-condition: The mouse needs to exist 
	p_mouse_ = p_mouse;
}
void Snake::move_tail()
{
	for (unsigned int i = tail.size() - 1; i > 0; i--)
	{
		tail[i].reset_position(tail[i - 1].get_x(), tail[i - 1].get_y());
	}
	tail[0].reset_position(get_x(), get_y());
}
/*char Snake::getTailSymbol() const
{
	for (unsigned int i = 0; i < tail.size(); i++)
	{
		return tail[i].getSymbol();
	}
}*/
bool Snake::get_tail_position(const int& x, const int& y) const {
	for (unsigned int i = 0; i < tail.size(); i++)
	{
		if ((tail[i].get_x() == x) && (tail[i].get_y() == y))
			return true;
	}
	return false;
}
void Snake::chase_mouse() {	 
	int snake_dx, snake_dy;
	//identify direction of travel
	set_direction(snake_dx, snake_dy);
	//go in that direction
	move_tail();
	update_position(snake_dx, snake_dy);
}
void Snake::set_direction(int& dx, int& dy)
{
	assert(p_mouse_ != nullptr);  //Pre-condition: The snake needs to know where the mouse is 
	//assume snake only move when necessary
	dx = 0; dy = 0;
		//update coordinate if necessary
	if (get_x() < p_mouse_->get_x())             //if snake on left of mouse
		dx = 1;                          //snake should move right
	else                                    //otherwise
		if (get_x() > p_mouse_->get_x())         //if snake on left of mouse
			dx = -1;                     //snake should move left
	if (get_y() < p_mouse_->get_y())             //if snake is above mouse
		dy = 1;                          //snake should move down
	else                                    //otherwise
		if (get_y() > p_mouse_->get_y())         //if snake is below mouse
			dy = -1;                     //snake should move up
}
void Snake::set_position(int x_, int y_) {
		reset_position(x_, y_);	//for serialization
		tail[0].reset_position(x_, y_);
		tail[1].reset_position(x_, y_);		//coil the snake
		tail[2].reset_position(x_, y_);
}


const RandomNumberGenerator Snake::rng_;
RandomNumberGenerator Snake::getRNG() const { return rng_; }
void Snake::position_at_random() {
	reset_position(rng_.get_random_value(SIZE), rng_.get_random_value(SIZE));
	for (int i = 0; i < tail.size(); i++)
		tail[i].reset_position(get_x(), get_y());

}
