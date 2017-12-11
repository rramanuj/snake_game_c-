#include "constants.h"
#include "MoveableGridItem.h"
class Nut : public MoveableGridItem {
public:
	//constructor
	Nut::Nut();
	//assessors
	bool has_been_collected() const;
	void disappear();
	void new_game();
private:
	bool collected_;
};

