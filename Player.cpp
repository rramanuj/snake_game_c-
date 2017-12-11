
#include "Player.h"
Player::Player()  {}
string Player::get_name() const {
	return name_;
}
int Player::get_score_amount() const {
	return score_.get_amount();
}
void Player::update_score_amount(const int& amount) {
	score_.update_amount(amount);
}

void Player::set_name(string name)
{
	name_ = name;
}
