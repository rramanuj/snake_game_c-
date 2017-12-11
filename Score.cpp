#include "Score.h"
Score::Score() : amount_(0) {}
int Score::get_amount() const
{
	return amount_;
}
void Score::update_amount(const int& amount)
{
	amount_ += amount;
}