#include "Score.h"
Score::Score() : amount_(0) {}
int Score::get_amount() const
{
	return amount_;
}
void Score::set_amount(int amount) {
	amount_ = amount;
}
void Score::update_amount(int amount)
{
	amount_ += amount;
}