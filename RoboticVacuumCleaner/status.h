#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "helpers.h"
#include "operation.h"


/*
Function to allow other modules to update the value of double start_time.

Parameters:
	x - a double which represents the value that start_time should be set to.
	
Returns:
	None

*/
void upd_start_time(double x);

/*
Function to allow other modules to update the value of boolian simover.

Parameters:
	x - an boolian which represents the state that simover should be set to.
	
Returns:
	None

*/
void upd_simover(bool x);

/*
Function to allow other modules to recieve the value of double start_time.

Parameters:
	None
	
Returns:
	a double which represents the value that start_time is currently set to.

*/
double get_start_time();

/*
Function to allow other modules to recieve the value of boolian simover.

Parameters:
	None
	
Returns:
	a boolian which represents the value that simover is currently set to.

*/
bool get_simover();

/*
Function that updates and formats the time status to be displayed in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void time();

/*
Function that updates and formats the battery status to be displayed in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void update_battery();

/*
Function that displays the student ID in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_sid(int w);

/*
Function that displays the elapsed time in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_elapsed(int w);

/*
Function that displays the device heading in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_heading(int w);

/*
Function that displays the device load weight in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_load(int w);

/*
Function that displays the device battery level in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_battery(int w, int h);

/*
Function that displays the current amount of each litter type in the status section of the command window.

Parameters:
	None
	
Returns:
	None

*/
void display_litter(int w);