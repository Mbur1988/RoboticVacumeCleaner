#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <cab202_graphics.h>
#include "helpers.h"
#include "my_helpers.h"

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

bool dock, rtb;
double csx, csy, vx, vy, vdx, vdy, tx[MAX_TRASH], ty[MAX_TRASH], sx[MAX_SLIME], sy[MAX_SLIME], dx[MAX_DUST], dy[MAX_DUST];
int load, d, s, T, num_trash, num_slime, num_dust, heading, batlvl;
char * vacuum =
"   @@@   "
"  @@@@@  "
" @@@@@@@ "
"@@@@@@@@@"
"@@@@@@@@@"
"@@@@@@@@@"
" @@@@@@@ "
"  @@@@@  "
"   @@@   "
;
char * chrgstn =
"#########"
"#########"
"#########"
;
char * trash =
"     &     "
"    &&&    "
"   &&&&&   "
"  &&&&&&&  "
" &&&&&&&&& "
"&&&&&&&&&&&"
;
char * slime =
" ~~~ "
"~~~~~"
"~~~~~"
"~~~~~"
" ~~~ "
;
char * dust =
"."
;


// Increase T by 1.
void upd_T()	{
	T = T+1;
}

// Increase s by 1.
void upd_s()	{
	s = s+1;
}

// Increase d by 1.
void upd_d()	{
	d = d+1;
}

// Update the value of dock.
void upd_dock(bool x)	{
	dock = x;
}

// Update the value of rtb.
void upd_rtb(bool x)	{
	rtb = x;
}

// Update the value of heading.
void upd_heading(int x)	{
	heading = x;
}

// Update load weight via standard input.
void load_input()	{
	load = get_int("New load weight?");
}

// Get the char array of vacuum.
char* get_vacuum()	{
	return vacuum;
}

// Get the char array of the charging station.
char* get_chrgstn()	{
	return chrgstn;
}

// Get the char array of trash.
char* get_trash()	{
	return trash;
}

// Get the char array of slime.
char* get_slime()	{
	return slime;
}

// Get the char array of dust.
char* get_dust()	{
	return dust;
}

// Return the value of num_trash.
int get_num_trash()	{
	return num_trash;
}

// Return the value of num_slime.
int get_num_slime()	{
	return num_slime;
}

// Return the value of num_dust.
int get_num_dust()	{
	return num_dust;
}

// Return the value of T.
int get_T()	{
	return T;
}

// Return the value of s.
int get_s()	{
	return s;
}

// Return the value of d.
int get_d()	{
	return d;
}

// Return the value of load.
int get_load()	{
	return load;
}

// Return the value of heading.
int get_heading() {
	int heading = atan2 (vdy,vdx) * 180/M_PI;
	return heading;
}

// Return the value of docked.
bool docked()	{
	return dock;
}

// Return the value of rtb.
bool get_rtb() {
	return rtb;
}

// Update vacuum position.
void update_vacuum(int w) {
	
	if (rtb == false) {	
	    int new_x = (round(vx + vdx) - VACUUM_WIDTH / 2)+3;
		int new_y = round(vy + vdy) - VACUUM_HEIGHT / 2;
		bool bounced = false;
		int ran = get_rand();
		
		if (pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum, 
				   csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, chrgstn)) {
			heading = get_heading();
			heading += ran;
			vdx = VACUUM_SPEED * cos(heading * M_PI/180);
			vdy = VACUUM_SPEED * sin(heading * M_PI/180);
			bounced = true;
		}
		
		if (new_x == 0 || new_x + VACUUM_WIDTH == screen_width() - 1) {
			// vertical bounce
			//getheading(); // command not required
			heading += ran;
			vdx = VACUUM_SPEED * cos(heading * M_PI/180);
			vdy = VACUUM_SPEED * sin(heading * M_PI/180);
			bounced = true;
		}

		if (new_y == 1 || new_y + VACUUM_HEIGHT == screen_height() - 6) {
			// horizontal bounce
			//getheading(); // command not required
			heading += ran;
			vdx = VACUUM_SPEED * cos(heading * M_PI/180);
			vdy = VACUUM_SPEED * sin(heading * M_PI/180);
			bounced = true;
		}
			
		if (!bounced) {
        vx += vdx;
        vy += vdy;
    }
	
	}
	
	if (rtb == true) {
		vdx = ((w/2)-3)-vx;
		vdy = 7-vy;
		double dockhed = atan2 (vdy,vdx);
		vdx = VACUUM_SPEED * cos(dockhed);
		vdy = VACUUM_SPEED * sin(dockhed);
		
		if (!pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum, 
			csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, chrgstn)) {
			vx += vdx;
			vy += vdy;
		}
		
		if (pixel_collision (vx + vdx, vy + vdy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum, 
			   csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, chrgstn)) {
			load = 0;
			if (batlvl < 100) {
				dock = true;
			}
			
			if (batlvl == 100) {
			   rtb = false;
			   dock = false;
			}
		}
	}
}

// Update trash amount and location.
void update_trash(int w, int h) {
	
	for (int i = 0; i < MAX_TRASH; ++i) {
		if(pixel_collision (tx[i], ty[i], TRASH_WIDTH, TRASH_HEIGHT, trash, 
		   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum)) {
		tx[i] = w;
		ty[i] = h;
		T -= 1;
		load += 20;
		}
	}
}

// Update slime amount and location.
void update_slime(int w, int h) {
	for (int i = 0; i < MAX_SLIME; ++i) {
		if(pixel_collision (sx[i], sy[i], SLIME_WIDTH, SLIME_HEIGHT, slime, 
		   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum)) {
		sx[i] = w;
		sy[i] = h;
		s -= 1;
		load += 5;
		}
	}
}

// Update dust amount and location.
void update_dust(int w, int h) {
	for (int i = 0; i < MAX_DUST; ++i) {
		if(pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, dust, 
		   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, vacuum)) {
		dx[i] = w;
		dy[i] = h;
		d -= 1;
		load += 1;
		}
	}
}

// Draw the charging station.
void draw_chrgstn() {
	draw_pixels(csx,csy,CHRGSTN_WIDTH,CHRGSTN_HEIGHT,chrgstn,true);
}

// Draw the vacuum.
void draw_vacuum() {
	draw_pixels(vx,vy,VACUUM_WIDTH,VACUUM_HEIGHT,vacuum,true);
}

// Draw the trash.
void draw_trash() {
	for (int i = 0; i < MAX_TRASH; ++i) {
		draw_pixels(tx[i],ty[i],TRASH_WIDTH,TRASH_HEIGHT,trash,true);
	}
}

// Draw the slime.
void draw_slime() {
	for (int i = 0; i < MAX_SLIME; ++i) {
		draw_pixels(sx[i],sy[i],SLIME_WIDTH,SLIME_HEIGHT,slime,true);
	}
}

// Draw the dust.
void draw_dust() {
	for (int i = 0; i < MAX_DUST; ++i) {
		draw_pixels(dx[i],dy[i],DUST_WIDTH,DUST_HEIGHT,dust,true);
	}
}
