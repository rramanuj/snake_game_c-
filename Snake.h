#include "Mouse.h"
#include <vector>
#include "RandomNumberGenerator.h"
#include "Tail.h"
class Snake : public MoveableGridItem {
	public:
		Snake();
		~Snake();
		//query
		bool has_caught_mouse() ;
		char output_tail() const;
		RandomNumberGenerator getRNG() const;
		bool get_tail_position(const int& x, const int& y)const;
		
		//mutator
		void spot_mouse(Mouse* p_mouse);
		void set_direction(int& dx, int& dy);
		void chase_mouse();
		void new_game();
		void move_tail();
		void set_tail(int x_, int y_);
		void set_position(int x_, int y_); //serialization
	private:

		Mouse* p_mouse_;
		vector<Tail> tail;
	//	const static RandomNumberGenerator rng_;
		void position_at_random();

};