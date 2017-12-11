#include "constants.h"
#include "FixedGridItem.h"
class Nut : public FixedGridItem {
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

