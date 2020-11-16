#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <cab202_graphics.h>
#include "helpers.h"
#include "my_helpers.h"


/*
Function to allow other modules to increase the value of T by 1.

Parameters:
	None
	
Returns:
	None

*/
void upd_T();

/*
Function to allow other modules to increase the value of s by 1.

Parameters:
	None
	
Returns:
	None

*/
void upd_s();

/*
Function to allow other modules to increase the value of d by 1.

Parameters:
	None
	
Returns:
	None

*/
void upd_d();

/*
Function to allow other modules to update the value of boolian dock.

Parameters:
	x - an boolian which represents the state that dock should be set to.
	
Returns:
	None

*/
void upd_dock(bool x);

/*
Function to allow other modules to update the value of boolian rtb.

Parameters:
	x - an boolian which represents the state that rtb should be set to.
	
Returns:
	None

*/
void upd_rtb(bool x);

/*
Function to allow other modules to update the value of integer heading.

Parameters:
	x - an intiger which represents the value that heading should be set to.
	
Returns:
	None

*/
void upd_heading(int x);

/*
Function to allow user to manually set the load weight via standard input.

Parameters:
	None
	
Returns:
	None

*/
void load_input();

/*
Function to allow other modules to get the char array value of the vacuum.

Parameters:
	None
	
Returns:
	Char array which represents the size and shape of the vacuum.

*/
char* get_vacuum();

/*
Function to allow other modules to get the char array value of the charging station.

Parameters:
	None
	
Returns:
	Char array which represents the size and shape of the charging station.

*/
char* get_chrgstn();

/*
Function to allow other modules to get the char array value of the trash.

Parameters:
	None
	
Returns:
	Char array which represents the size and shape of the trash.

*/
char* get_trash();

/*
Function to allow other modules to get the char array value of the slime.

Parameters:
	None
	
Returns:
	Char array which represents the size and shape of the slime.

*/
char* get_slime();

/*
Function to allow other modules to get the char array value of the dust.

Parameters:
	None
	
Returns:
	Char array which represents the size and shape of the dust.

*/
char* get_dust();

/*
Function to allow other modules to recieve the value of integer num_trash.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces trash to be visibly displayed initially.

*/
int get_num_trash();

/*
Function to allow other modules to recieve the value of integer num_slime.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces slime to be visibly displayed initially.

*/
int get_num_slime();

/*
Function to allow other modules to recieve the value of integer num_dust.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces dust to be visibly displayed initially.

*/
int get_num_dust();

/*
Function to allow other modules to recieve the value of integer T.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces of trash currently visibly displayed.

*/
int get_T();

/*
Function to allow other modules to recieve the value of integer s.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces of slime currently visibly displayed.

*/
int get_s();

/*
Function to allow other modules to recieve the value of integer d.

Parameters:
	None
	
Returns:
	a integer which represents the number of pieces of dust currently visibly displayed.

*/
int get_d();

/*
Function to allow other modules to recieve the value of integer load.

Parameters:
	None
	
Returns:
	a integer which represents the load weight currently acting on the device.

*/
int get_load();

/*
Function to allow other modules to recieve the value of integer heading.

Parameters:
	None
	
Returns:
	a integer which represents the current heading of the device in degrees.

*/
int get_heading();

/*
Function to allow other modules to recieve the value of boolian docked.

Parameters:
	None
	
Returns:
	A boolian which represents the whether the device is currently docked at the charging station.

*/
bool docked();

/*
Function to allow other modules to recieve the value of boolian rtb.

Parameters:
	None
	
Returns:
	A boolian which represents the whether the device is currently set to return to base mode.

*/
bool get_rtb();

/*
Function to update the x and y locational coordinates of the vacuum.

Parameters:
	w - an integer which represents the width of the terminal window.
	
Returns:
	None

*/
void update_vacuum(int w);

/*
Function to indetify the pixel level collision between the vacuum cleaner and the trash.
updates number of visible trash accordingly.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void update_trash(int w, int h);

/*
Function to indetify the pixel level collision between the vacuum cleaner and the slime.
updates number of visible slime accordingly.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void update_slime(int w, int h);

/*
Function to indetify the pixel level collision between the vacuum cleaner and the dust.
updates number of visible dust accordingly.

Parameters:
	w - an integer which represents the width of the terminal window.
	h - an integer which represents the height of the terminal window.
	
Returns:
	None

*/
void update_dust(int w, int h);

/*
Function to draw the charging station.

Parameters:
	None
	
Returns:
	None

*/
void draw_chrgstn();

/*
Function to draw the vacuum.

Parameters:
	None
	
Returns:
	None

*/
void draw_vacuum();

/*
Function to draw the trash.

Parameters:
	None
	
Returns:
	None

*/
void draw_trash();

/*
Function to draw the slime.

Parameters:
	None
	
Returns:
	None

*/
void draw_slime();

/*
Function to draw the dust.

Parameters:
	None
	
Returns:
	None

*/
void draw_dust();