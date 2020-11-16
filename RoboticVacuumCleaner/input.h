#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "helpers.h"
#include "my_helpers.h"
#include "setup.h"
#include "operation.h"
#include "status.h"


/* 
Function to move the device one unit north (up on the terminal).

Parameters:
	None
	
Returns:
	None

*/
void do_i();

/* 
Function to move the device one unit west (left on the terminal).

Parameters:
	None
	
Returns:
	None

*/
void do_j();

/* 
Function to move the device one unit south (down on the terminal).

Parameters:
	None
	
Returns:
	None

*/
void do_k(int h);

/* 
Function to move the device one unit east (right on the terminal).

Parameters:
	None
	
Returns:
	None

*/
void do_l(int w);

/* 
Function to drop a piece of trash (large rubbish) on the floor.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void do_t(int w, int h);

/* 
Function to drop a piece of slime (medium rubbish) on the floor.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void do_s(int w, int h);

/* 
Function to drop a piece of dust (small rubbish) on the floor.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void do_d(int w, int h);

/* 
Function to move the device to a new location and specify a new direction.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void do_v(int w, int h);

/* 
Function to display help screen.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void do_help(int w, int h);