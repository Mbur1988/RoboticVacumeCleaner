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

#define VACUUM_SPEED 0.2
#define VACUUM_WIDTH 9
#define VACUUM_HEIGHT 9
#define CHRGSTN_WIDTH 9
#define CHRGSTN_HEIGHT 3
#define TRASH_WIDTH 11
#define TRASH_HEIGHT 6
#define MAX_TRASH 5
#define SLIME_WIDTH 5
#define SLIME_HEIGHT 5
#define MAX_SLIME 10
#define DUST_WIDTH 1
#define DUST_HEIGHT 1
#define MAX_DUST 1000

double csx, csy, vx, vy, vdx, vdy, tx[MAX_TRASH], ty[MAX_TRASH], sx[MAX_SLIME], sy[MAX_SLIME], dx[MAX_DUST], dy[MAX_DUST];


// move the device one unit north.
void do_i()	{
	if (vy > 5) {
		vy =  round(vy) - 1;
	}
	if (pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum(), 
		csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn()))	{
		vy += 1;
	}
}

// move the device one unit west.
void do_j()	{
	if (vx > 1) {
		vx = round(vx) - 1;
	}
	if (pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum(), 
		csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn()))	{
		vx += 1;
	}
}

// move the device one unit south.
void do_k(int h)	{
	if (vy < (h-3)-VACUUM_HEIGHT) {
		vy = round(vy) + 1;
	}
}

// move the device one unit east.
void do_l(int w)	{
	if (vx < (w-1)-VACUUM_WIDTH) {
		vx = round(vx) + 1;
	}
	if (pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum(), 
		csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn()))	{
		vx -= 1;
	}
}

// drop a piece of trash on the floor.
void do_t(int w, int h)	{
	bool setter = false;
	for (int i = 0; i < MAX_TRASH; ++i) {
		if (tx[i] == w && setter == false)	{
			int x = get_int("Enter x coordinate");
			if (x < 1)	{
				x = 1;
			}
			if (x > (w - 1 - TRASH_WIDTH))	{
				x = (w - 1 - TRASH_WIDTH);
			}
			int y = get_int("Enter y coordinate");
			if (y < 5)	{
				y = 5;
			}
			if (y > (h - 3 - TRASH_HEIGHT))	{
				y = (h - 3 - TRASH_HEIGHT);
			}
			tx[i] = x;
			ty[i] = y;
			upd_T();
			setter = true;
		}
	}
}

// drop a piece of slime on the floor.
void do_s(int w, int h)	{
	bool setter = false;
	for (int i = 0; i < MAX_SLIME; ++i) {
		if (sx[i] == w && setter == false)	{
			int x = get_int("Enter x coordinate");
			if (x < 1)	{
				x = 1;
			}
			if (x > (w - 1 - SLIME_WIDTH))	{
				x = (w - 1 - SLIME_WIDTH);
			}
			int y = get_int("Enter y coordinate");
			if (y < 5)	{
				y = 5;
			}
			if (y > (h - 3 - SLIME_HEIGHT))	{
				y = (h - 3 - SLIME_HEIGHT);
			}
			sx[i] = x;
			sy[i] = y;
			upd_s();
			setter = true;
		}
	}
}

// drop a piece of dust on the floor.
void do_d(int w, int h)	{
	bool setter = false;
	for (int i = 0; i < MAX_DUST; ++i) {
		if (dx[i] == w && setter == false)	{
			int x = get_int("Enter x coordinate");
			if (x < 1)	{
				x = 1;
			}
			if (x > (w - 1 - DUST_WIDTH))	{
				x = (w - 1 - DUST_WIDTH);
			}
			int y = get_int("Enter y coordinate");
			if (y < 5)	{
				y = 5;
			}
			if (y > (h - 3 - DUST_HEIGHT))	{
				y = (h - 3 - DUST_HEIGHT);
			}
			dx[i] = x;
			dy[i] = y;
			upd_d();
			setter = true;
		}
	}
}

// move the device to a new location and specify a new direction.
void do_v(int w, int h)	{
	int x = get_int("Enter x coordinate");
	if (x < 1)	{
		x = 1;
	}
	if (x > (w - 1 - VACUUM_WIDTH))	{
		x = (w - 1 - VACUUM_WIDTH);
	}
	int y = get_int("Enter y coordinate");
	if (y < 5)	{
		y = 5;
	}
	if (y > (h - 3 - VACUUM_HEIGHT))	{
		y = (h - 3 - VACUUM_HEIGHT);
	}
	vx = x;
	vy = y;
	
	int head = get_int("Enter new heading");
	vdx = VACUUM_SPEED * cos(head * M_PI/180);
	vdy = VACUUM_SPEED * sin(head * M_PI/180);
}

// display help screen.
void do_help(int w, int h)	{
	char * help =
	"+------------------------------------------------------------------------+"
	"|                                                                        |"
	"|                                                                        |"
	"|       b - tell the device to stop cleaning and return to base          |"
	"|           i.e. step repeatedly towards the charging dock.              |"
	"|       d - drop a piece of dust (small rubbish) on the floor.           |"
	"|       i - push the device one unit north (up on the terminal).         |"
	"|       j - push the device one unit west (left on the terminal).        |"
	"|       k - push the device one unit south (down on the terminal).       |"
	"|       l - push the device one unit east (right on the terminal).       |"
	"|       m - set the millisecond delay between successive                 |"
	"|           invocations of the loop function.                            |"
	"|       o - set the time-out period, that is, the total permitted        |"
	"|           run time, measured in seconds.                               |"
	"|       p - cause the device to start moving (if it is stationary)       |"
	"|           or stop moving (if it is mobile).                            |"
	"|       q - quit simulation.                                             |"
	"|       r - reset simulation.                                            |"
	"|       s - drop a piece of slime (medium rubbish) on the floor.         |"
	"|       t - drop a piece of trash (large rubbish) on the floor.          |"
	"|       v - move the device to a new location and specify a new          |"
	"|           direction.                                                   |"
	"|       w - change the amount (weight) of the rubbish currently on       |"
	"|           board the device.                                            |"
	"|       y - change the battery level of the device.                      |"
	"|                                                                        |"
	"|                                                                        |"
	"|                   Press any key to exit help menu                      |"
	"|                                                                        |"
	"|                                                                        |"
	"+------------------------------------------------------------------------+"
	;
	int help_w = 74;
	int help_h = 31;
	clear_screen();
	int hx = ((w)/2)-help_w/2;
	int hy = ((h)/2)-help_h/2;
	draw_pixels(hx,hy,help_w,help_h,help,false);
	show_screen();
	int ch = wait_char();
	if (ch >= ' ') {}
}
