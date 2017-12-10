#include "Mouse.h"
#include <vector>
#include "RandomNumberGenerator.h"
#include "Tail.h"
class Snake : public MoveableGridItem {
	public:
		Snake();
		~Snake();
		bool has_caught_mouse() ;
		void spot_mouse(Mouse* p_mouse);
		void chase_mouse();
		RandomNumberGenerator getRNG() const;
		void set_direction(int& dx, int& dy);
			
		void move_tail();
		bool get_tail_position(const int& x, const int& y)const;
		void place_randomly();
	private:

		Mouse* p_mouse_;
		vector<Tail> tail;
		const static RandomNumberGenerator rng_;
		void position_at_random();

};