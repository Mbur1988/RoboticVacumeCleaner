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
#include "input.h"

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


bool quit = false;
bool pause = true;

int delay = 10;
int timeout = -1;


double csx, csy, vx, vy, vdx, vdy, tx[MAX_TRASH], ty[MAX_TRASH], sx[MAX_SLIME], sy[MAX_SLIME], dx[MAX_DUST], dy[MAX_DUST];
int w, h, secs, batlvl, batupd; 



// Populate the status windows at the top of the command window.
void populate_status() {

	// Display student id
	display_sid(w);
	// Display time elapsed
	display_elapsed(w);
	// Display Heading
	display_heading(w);
	// Display Load Weight
	display_load(w);
	// Display Battery level
	display_battery(w, h);
	// Display Litter
	display_litter(w);
}

// Draw all elements of the program and update display.
void draw_all() {
    clear_screen();
    draw_border(w,h);
    populate_status();
	draw_chrgstn();
	draw_dust();
	draw_slime();
	draw_trash();
	draw_vacuum();
    show_screen();
}

// Setup all elements of the program.
void setup() {
	
    // Insert setup logic here 	
	get_screen_size(&w, &h);
	upd_start_time(get_current_time());
	upd_dock(false);
	upd_rtb(false);
	setup_chrgstn(w);
	setup_vacuum(w, h);
	setup_trash(w, h);
	setup_slime(w, h);
	setup_dust(w, h);
	batlvl = 100;
	draw_all();
	}

// Update all elements of the program.
void update_all() {
	update_vacuum(w);
	if (!get_rtb()) {
		update_trash(w, h);
		update_slime(w, h);
		update_dust(w, h);
	}
}

// Reset the program to startup conditions.
void reset() {
    setup();
	pause = true;
}

// Cause the device to either pause or unpause based on its current status.
void do_pause() {
	if (pause == true){
		pause = false;
	}
	else if (pause == false) {
		pause = true;
	}
}

/* Standard input jump table.
 *
 *  Jump table which chooses the action (if any) which corresponds to a
 *  supplied command character.
 *
 *  Parameters:
 *      ch: a command character. Currently recognised comands are listed in
 *          the do_help function.
 */
void do_operation(int ch) {

	if (ch == 'r') {
        reset();
    }
	
    else if (ch == 'b') {
        upd_rtb(true);
	}
    
	else if (ch == 'y') {
		batlvl = get_int("New battery level?");
    }
	
	else if (ch == 'w') {
		load_input();
		upd_rtb(false);
    }
	
	else if (ch == 'i') {
		do_i();
    }	
	
	else if (ch == 'j') {
		do_j();
	}	
	
	else if (ch == 'k') {
		do_k(h);
    }	
	
	else if (ch == 'l') {
		do_l(w);
    }
	
	else if (ch == 'p') {
		do_pause();
    }
	
	else if (ch == 't') {
		do_t(w, h);
	}
	
	else if (ch == 's') {
		do_s(w, h);
	}
	
	else if (ch == 'd') {
		do_d(w, h);
	}
	
	else if (ch == 'v') {
		do_v(w, h);
	}	
	
	else if (ch == '?') {
		do_help(w, h);
}
	
	else if (ch == 'm') {
		delay = get_int("Enter new delay in milli seconds");
	}

	else if (ch == 'o') {
		timeout = get_int ("Enter new time out limit in seconds");
	}

}

// Initialise game over sequence.
void game_over()	{
		char * qmessage =
	"+-----------------------------------+"
	"|                                   |"
	"|                                   |"
	"|                                   |"
	"|             Game Over             |"
	"|                                   |"
	"|           Press any key           |"
	"|                                   |"
	"|                                   |"
	"|                                   |"
	"+-----------------------------------+"
	;
	int mx = ((w)/2)-18;
	int my = ((h)/2)-6;
	draw_pixels(mx,my,37,11,qmessage,false);
	show_screen();
	int ch = wait_char();
	quit = true;
	upd_simover(false);
	if (ch >= ' ') {
	}
}

// Initialise simulation over sequence.
void sim_over() {
	char * somessage =
	"+-----------------------------------+"
	"|                                   |"
	"|                                   |"
	"|                                   |"
	"|          Simulation Over          |"
	"|         Press 'q' to quit         |"
	"|          or 'r' to reset          |"
	"|                                   |"
	"|                                   |"
	"|                                   |"
	"+-----------------------------------+"
	;
	int mx = ((w)/2)-18;
	int my = ((h)/2)-6;
	draw_pixels(mx,my,37,11,somessage,false);
	show_screen();
	int ch = wait_char();
	
	if (ch == 'q') {
		game_over();
    }
	
	else if (ch == 'r') {
		reset();
		upd_simover(false);
    }
	
	else if (ch >= ' ') {
		sim_over();
    }
	
}

// The loop function: called once per time slice to run the simulation.
void loop() {
    // Insert loop logic here.

	int ch = get_char();

	if (get_simover()) {
		sim_over();
		batlvl+=1;
	}
	
	else if (ch == 'q' || (get_current_time()-get_start_time() >= timeout && timeout >= 0)) {
        game_over();
    }
	
    else if (ch >= ' ') {
        do_operation(ch);
    }
	
	else if (ch != 'q' && pause == false) {
        if ((get_load() > 45 || batlvl < 25) && !get_rtb()) {
			upd_rtb(true);
		}
		update_all();
	} 
	
	time();
	draw_all();
}

// Program start and event loop.
int main(void) {
	srand((unsigned) get_current_time());
	setup_screen();
    setup();
		
    while (!quit) {
 		loop();
		timer_pause(delay);
	}

    return 0;
}