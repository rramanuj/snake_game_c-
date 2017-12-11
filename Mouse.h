// Mouse.h: UserInterface for the Mouse class
//////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// Date       Programmer    Amendments made and justification (if needed)
//---------------------------------------------------------------------
// 
//
//---------------------------------------------------------------------

#if !defined(MouseH)
#define MouseH

#include "constants.h"
#include "Underground.h"
#include "MoveableGridItem.h"
#include "Nut.h"

class Mouse : public MoveableGridItem{
	public:
		//constructor
		Mouse::Mouse();
		//assessors
		bool is_alive() const;
		bool has_escaped() const;
		bool has_reached_a_hole(const Underground& ug) const;
		//mutators
		void die();
		bool can_collect_nut(const Nut& n) const;
		void escape_into_hole();
		void scamper(char k);
		char symbol_;
		void new_game();

	private:
		//data members
		bool alive_;
		bool escaped_;
		int mouse_dx_;
		int mouse_dy_;
		//supporting functions 
		void position_in_middle_of_grid();
};

#endif // !defined(MouseH)
