// constants.h: list of constants used in the system 
//////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// Date       Programmer    Amendments made and justification (if needed)
//---------------------------------------------------------------------
// 
//
//---------------------------------------------------------------------
#if !defined(constantsH)
#define constantsH 

//--------define constants
//________________________________________________
//define constants

//defining the size of the grid
#define SIZE      (20)	//grid dimension

//defining symbols used for display of the grid and grid items
#define SNAKEHEAD ('S')	//snake symbol
#define MOUSE     ('M')	//mouse symbol
#define HOLE      ('H')	//hole symbol
#define FREECELL  ('.')	//empty cell on grid
#define NUT		  ('N') //nut symbol
#define TAIL ('T') //tail symbol

//defining the command letters to move the mouse on the maze
#define UP        (72)	//up arrow
#define DOWN      (80)	//down arrow
#define RIGHT     (77)	//right arrow
#define LEFT      (75)	//left arrow

//defining the other command letters
#define QUIT      ('Q')	//to end game

#endif // !defined(constantsH)
