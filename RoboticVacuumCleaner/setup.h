#include <string.h>
#include <cab202_graphics.h>
#include "helpers.h"
#include "my_helpers.h"
#include "operation.h"


/*
Function to draw all boarders in the command window.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void draw_border(int w, int h);

/*
Function to setup positional parameters of the charging station based on the command window dimensions.

Parameters:
	w - an integer which represents the width of the terminal window.	
	
Returns:
	None

*/
void setup_chrgstn(int w);

/*
Function to setup initial positional and directional parameters of the vacuum based on the command window dimensions.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void setup_vacuum(int w, int h);

/*
Function to setup initial positional parameters of the trash based on the command window dimensions.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void setup_trash(int w, int h);

/*
Function to setup initial positional parameters of the slime based on the command window dimensions.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void setup_slime(int w, int h);

/*
Function to setup initial positional parameters of the dust based on the command window dimensions.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void setup_dust(int w, int h);