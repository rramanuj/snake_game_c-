#include "Mouse.h"
#include "RandomNumberGenerator.h"
class Snake {
	public:

		Snake();
		~Snake();
		bool is_at_position(int x, int y);  
		bool has_caught_mouse() ;
		void spot_mouse(Mouse* p_mouse);
		void chase_mouse();
		RandomNumberGenerator getRNG() const;
		void set_direction(int& dx, int& dy);
		void position_at_random();
		void update_position(int dx, int dy);
		char symbol_;
		int getX() const;
		int getY() const;
		void set_position(int x, int y);
	private:

		int x_, y_;		//moved to private, accessed via getters
		Mouse* p_mouse_;
		const static RandomNumberGenerator rng_;

};