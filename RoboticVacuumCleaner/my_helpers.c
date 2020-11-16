#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <cab202_graphics.h>
#include <cab202_timers.h>


// Pixel level collision detection.
bool pixel_collision (int x0, int y0, int w0, int h0, char* pixels0, 
					  int x1, int y1, int w1, int h1, char* pixels1)
{

	for (int i = 0; i < strlen(pixels0); i++) 
	{
		if (pixels0[i] != ' ')
		{	
			for (int j = 0; j < strlen(pixels1); j++) 
			{
				if (pixels1[j] != ' ')
				{
					int x_po = x0 + i%w0;
					int y_po = y0 + (i-(i%w0))/w0;
					int x_p1 = x1 + j%w1;
					int y_p1 = y1 + (j-(j%w1))/w1;
					if (x_po == x_p1 && y_po == y_p1)
						{
							return true;
						}
				}
			}
		}
	}
	return false;
}

// Draw char* of pixels.
void draw_pixels (int left, int top, int width, int height, char* bitmap, bool space_is_transparent)
{
	for (int j = 0; j <= height-1; j++) 
	{
		for (int i = 0; i <= width-1; i++) 
		{
			if (bitmap[i+j*width] != ' ')
			{
				draw_char(left+i,top+j,bitmap[i+j*width]); // Draw bitmap[i+j*width] at (left+i,top+j);
			}
			else if (space_is_transparent == false)
			{
				draw_char(left+i,top+j,' '); // Draw ' ' at (left+i,top+j);
			}
		}
	}
}

// Get random number between +/- 30-60.
int get_rand() {
		int ran = rand() % 58;
	if (ran <= 28) {
		ran -= 59;
	}
	else if (ran > 28) {
		ran += 2;
	}
	return ran;
}