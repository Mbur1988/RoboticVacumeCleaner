#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>
#include "helpers.h"
#include "operation.h"

bool pause, simover = false;
double start_time;
int secs, batlvl, batupd;
char timestr[6];


// update the value of start_time.
void upd_start_time(double x)	{
	start_time = x;
}

// update the value of simover.
void upd_simover(bool x)	{
	simover = x;
}

// return the value of start_time.
double get_start_time()	{
	return start_time;
}

// return the value of simover.
bool get_simover()	{
	return simover;
}

// update and formats the time.
void time() {
	batupd = secs;

	double elapsed = get_current_time()-start_time;
	int mins = (elapsed / 60);
	secs = elapsed - (60*mins);

	timestr[0] = '0' + mins / 10;
	timestr[1] = '0' + mins % 10;
	timestr[2] = ':';
	timestr[3] = '0' + secs / 10;
	timestr[4] = '0' + secs % 10;
	timestr[5] = '\0';
}

// update and formats the battery.
void update_battery() {
	
	if (!docked() && batupd != secs && pause == false && batlvl > 0) {
		batlvl -= 1;
	}
	
	if (docked() && pause == false && batlvl < 100) {
	
	double time = get_current_time();
	timer_pause(1);
	double time2 = get_current_time() - time;
		while (time2<0.03) { // 0.01 already being delayed as part of loop delay
			time2 = get_current_time();
			time2 -= time;
		}
		batlvl += 1;
	}	
	
	if (batlvl == 0) {
		simover = true;
	}
}

// display student id.
void display_sid(int w)	{
	char * sid = "n9801154";
	int hsidlen = strlen(sid)/2;
	draw_string(((w-1)/6)-hsidlen,1,sid);
}

// display time elapsed.
void display_elapsed(int w)	{
	char* time_message = "Elapsed:   :  ";
	int timelen = strlen(time_message);
	int htimelen = timelen/2;
	draw_string(((w-1)/6-htimelen),3,time_message);
	draw_string(((w-1)/6+2),3,timestr);
}

// display heading.
void display_heading(int w)	{
	char * hed = "Heading:    ";
	int hhedlen = strlen(hed)/2;
	draw_string(((w-1)/2)-hhedlen,1,hed);
	if (get_heading() < 0) {
		draw_int(((w-1)/2)+3,1,get_heading()+360);
	}
	else	{
	draw_int(((w-1)/2)+3,1,get_heading());
	}
}

// display load weight.
void display_load(int w)	{
	char * low = "Load Weight (g):   ";
	int hlowlen = strlen(low)/2;
	draw_string(((w-1)/2)-hlowlen,3,low);
	draw_int(((w-1)/2)+hlowlen-1,3,get_load());
}

// display battery level.
void display_battery(int w, int h)	{
	char * bat1;
	char * bat2;
	int lvlx;
	char* dockmessage = "Docked";
	
	if (batlvl<100) {
		bat1 = "Battery:   %";
		bat2 = "Charging:   %";
		lvlx = ((w-1)/6)*5+3;
	}
		if (batlvl==100) {
		bat1 = "Battery:    %";
		//bat2 = "Charging:    %";
		lvlx = ((w-1)/6)*5+3;
	}
	
	int hbatlen = strlen(bat1)/2;
	int hdockmessage = strlen(dockmessage)/2;
	if (!docked()) {
		draw_string(((w-1)/6)*5-hbatlen,1,bat1);
		update_battery();
		draw_int(lvlx,1,batlvl);
	}
	if (docked()) {
		draw_string(((w-1)/6)*5-hbatlen,1,bat2);
		draw_string(((w-1)/2)-hdockmessage,h-2,dockmessage);
		update_battery();
		draw_int(lvlx+1,1,batlvl);
	}
}

// display litter.
void display_litter(int w)	{
	char * lit = "Litter (T,s,d):   ,  ,  ";
	int hlitlen = strlen(lit)/2;
	draw_string(((w-1)/6)*5-hlitlen,3,lit);
	draw_int(((w-1)/6)*5+4,3,get_T());
	draw_int(((w-1)/6)*5+7,3,get_s());
	draw_int(((w-1)/6)*5+10,3,get_d());
}
