#include <string.h>
#include <cab202_graphics.h>
#include "helpers.h"
#include "my_helpers.h"
#include "operation.h"

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
int load, d, s, T, num_trash, num_slime, num_dust;


// draw horizontal lines using '-'.
void horizontal_lines(int w, int h) {
	draw_line( 1, 0, w-2, 0, '-');
	draw_line( 1, 2, w-2, 2, '-');
	draw_line( 1, 4, w-2, 4, '-');
	draw_line( 1, h-3, w-2, h-3, '-');
}
	
// draw vertical lines using '|'.
void vertical_lines(int w, int h) {
	
	draw_line( 0, 0, 0, h-3, '|');
	draw_line( ((w-1)/3), 0, ((w-1)/3), 4, '|');
	draw_line( ((w-1)/3)*2, 0, ((w-1)/3)*2, 4, '|');
	draw_line( w-1, 0, w-1, h-3, '|');
}

// draw line joins using '+'.
void line_joins(int w, int h) {
	draw_line( 0, 0, 0, 0, '+');
	draw_line( w-1, 0, w-1, 0, '+');
	draw_line( 0, 4, 0, 4, '+');
	draw_line( w-1, 4, w-1, 4, '+');
	draw_line( 0, h-3, 0, h-3, '+');
	draw_line( w-1, h-3, w-1, h-3, '+');
	draw_line( 0, 2, 0, 2, '+');
	draw_line( ((w-1)/3), 0, ((w-1)/3), 0, '+');
	draw_line( ((w-1)/3), 2, ((w-1)/3), 2, '+');
	draw_line( ((w-1)/3), 4, ((w-1)/3), 4, '+');
	draw_line( ((w-1)/3)*2, 0, ((w-1)/3)*2, 0, '+');
	draw_line( ((w-1)/3)*2, 2, ((w-1)/3)*2, 2, '+');
	draw_line( ((w-1)/3)*2, 4, ((w-1)/3)*2, 4, '+');
	draw_line( w-1, 2, w-1, 2, '+');
}

// function to draw boarders.
void draw_border(int w, int h) {	
	horizontal_lines(w,h);
	vertical_lines(w,h);
	line_joins(w,h);
}

// setup charge station values.
void setup_chrgstn(int w) {
	csx = (((w)/2)-4); 
	csy = 5;
}

// setup vacuum values.
void setup_vacuum(int w, int h) {
    
	vx = ((w/2)-(VACUUM_WIDTH/2));
	vy = (h/2)-(VACUUM_HEIGHT/2);

    vdx = 0;
    vdy = 1*VACUUM_SPEED;
	
	load = 0;
}

// setup trash values.
void setup_trash(int w, int h) {
	num_trash = get_int("Enter amount of trash (max 5)");
	if (get_num_trash() > MAX_TRASH) {
			num_trash = MAX_TRASH;
		}
	T = get_num_trash();
	for (int i = 0; i < MAX_TRASH; ++i) {
		if (i < get_num_trash()) {
			
			tx[i] = (rand() % (w - 1 - TRASH_WIDTH))+1;
			ty[i] = (rand() % (h - 1 - TRASH_HEIGHT-6))+5;
			
			if(pixel_collision (tx[i], ty[i], TRASH_WIDTH, TRASH_HEIGHT, get_trash(), 
			   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum())||pixel_collision (tx[i], ty[i], TRASH_WIDTH, TRASH_HEIGHT, get_trash(), 
			   csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn())) {
				--i;
			}
			
			for (int j = 0; j < i; ++j) {
				
				if(pixel_collision (tx[i], ty[i], TRASH_WIDTH, TRASH_HEIGHT, get_trash(), 
			   tx[j], ty[j], TRASH_WIDTH, TRASH_HEIGHT, get_trash())) {
					--i;
			   }
			}
		}
		else {
			tx[i] = w;
			ty[i] = h;
		}
	}
}

// setup slime values.
void setup_slime(int w, int h) {
	num_slime = get_int("Enter amount of slime (max 10)");
	if (num_slime > MAX_SLIME) {
			num_slime = MAX_SLIME;
		}
	s = num_slime;	
	for (int i = 0; i < MAX_SLIME; ++i) {
		if (i < num_slime) {
			
			sx[i] = (rand() % (w - 1 - SLIME_WIDTH))+1;
			sy[i] = (rand() % (h - 1 - SLIME_HEIGHT-6))+5;
			
			if(pixel_collision (sx[i], sy[i], SLIME_WIDTH, SLIME_HEIGHT, get_slime(), 
			   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum())||pixel_collision (sx[i], sy[i], SLIME_WIDTH, SLIME_HEIGHT, get_slime(), 
			   csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn())) {
				--i;
			}
						
			for (int j = 0; j < num_trash; ++j) {
				
				if(pixel_collision (sx[i], sy[i], SLIME_WIDTH, SLIME_HEIGHT, get_slime(), 
			   tx[j], ty[j], TRASH_WIDTH, TRASH_HEIGHT, get_trash())) {
					--i;
			   }
			}
			
			for (int j = 0; j < i; ++j) {
				
				if(pixel_collision (sx[i], sy[i], SLIME_WIDTH, SLIME_HEIGHT, get_slime(), 
			   sx[j], sy[j], SLIME_WIDTH, SLIME_HEIGHT, get_slime())) {
					--i;
			   }
			}
		}
		else {
			sx[i] = w;
			sy[i] = h;
		}
	}
}

// setup dust vlaues.
void setup_dust(int w, int h) {
	num_dust = get_int("Enter amount of dust (max 1000)?");
	if (num_dust > MAX_DUST) {
			num_dust = MAX_DUST;
		}
	d = num_dust;
	for (int i = 0; i < MAX_DUST; ++i) {
		if (i < num_dust) {
			
			dx[i] = (rand() % (w - 1 - DUST_WIDTH))+1;
			dy[i] = (rand() % (h - 1 - DUST_HEIGHT-6))+5;
			
			if(pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, get_dust(), 
			   vx, vy, VACUUM_WIDTH, VACUUM_HEIGHT, get_vacuum())||pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, get_dust(), 
			   csx, csy, CHRGSTN_WIDTH, CHRGSTN_HEIGHT, get_chrgstn())) {
				--i;
			}
							
			for (int j = 0; j < num_trash; ++j) {
				
				if(pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, get_dust(), 
				   tx[j], ty[j], TRASH_WIDTH, TRASH_HEIGHT, get_trash())) {
					--i;
			   }
			}
			
			for (int j = 0; j < num_slime; ++j) {
				
				if(pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, get_dust(), 
				   sx[j], sy[j], SLIME_WIDTH, SLIME_HEIGHT, get_slime())) {
					--i;
			   }
			}
			
			for (int j = 0; j < i; ++j) {
				
				if(pixel_collision (dx[i], dy[i], DUST_WIDTH, DUST_HEIGHT, get_dust(), 
			   dx[j], dy[j], DUST_WIDTH, DUST_HEIGHT, get_dust())) {
					--i;
			   }
			}
		}
		else {
			dx[i] = w;
			dy[i] = h;
		}
	}
}
