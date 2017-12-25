#include "constants.h"
#include "RandomNumberGenerator.h"
#include "MoveableGridItem.h"
class Nut : public MoveableGridItem {
public:
	//constructor
	Nut::Nut();
	//assessors
	bool has_been_collected() const;
	void disappear();
	void new_game();
	RandomNumberGenerator getRNG() const;
	void position_at_random();
private:
	bool collected_;
	const static RandomNumberGenerator rng_;
};

