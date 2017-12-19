#include "Nut.h"
Nut::Nut() : MoveableGridItem(NUT, 8, 9) { collected_ = false; };

bool Nut::has_been_collected() const {
	return collected_;
}
void Nut::disappear() {
	collected_ = true;
}
void Nut::new_game() {
	collected_ = false;
}


