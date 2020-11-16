#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <cab202_graphics.h>
#include <cab202_timers.h>


/*
pixel_collision checks whether two images rendered in the terminal window 
are undergoing pixel-level collision. Rather than bounding box collision in which the 
containing rectangles overlap, pixel level collision occurs when (and only when) one or more 
opaque pixels of the images appear at the same location in the screen frame of reference.

Parameters:
    x0 – an integer which specifies the horizontal offset of the left edge of the first image.
    y0 – an integer which specifies the vertical offset of the top edge of the first image.
    w0 – an integer which specifies the width of the first image.
    h0 – an integer which specifies the height of the first image.
	pixels0 – an array of char which defines the image data. This array is guaranteed to refer 
			  to at least w0×h0 valid elements.
    x1 – an integer which specifies the horizontal offset of the left edge of the second image.
    y1 – an integer which specifies the vertical offset of the top edge of the second image.
    w1 – an integer which specifies the width of the second image.
    h1 – an integer which specifies the height of the second image.
    pixels1 – an array of char which defines the image data. This array is guaranteed to refer 
			  to at least w1×h1 valid elements.
Returns:
    Returns true if and only if at least one screen location would be covered by an opaque 
	element of both images. 
	An element is opaque if and only if it is not the space character, ' '.
*/
 bool pixel_collision (int x0, int y0, int w0, int h0, char* pixels0, 
					   int x1, int y1, int w1, int h1, char* pixels1);
 
/* 
draw_pixels renders a given bitmap image into the screen using ZDK functions.

Parameters:
	left – an integer which specifies the horizontal offset of the top-left corner of the 
		   image, if it were to be rendered.
    top – an integer which specifies the vertical offset of the top-left corner of the image,
		  if it were to be rendered.
    width – an integer which specifies the width of the image that would be rendered.
    height – an integer which specifies the height of the image that would be rendered.
    bitmap – a char array which contains the pixel data of the bitmap. This array is guaranteed
			 to have at least width×height elements.
    space_is_transparent – a boolean value which determines if we can see through spaces. If 
						   this is true, then we should skip any pixels occupied by a space 
						   (' ') in the bitmap. This is also called “transparent spaces” mode.
						   Otherwise, spaces should be opaque.
Returns:
	No value is returned.

*/
 void draw_pixels (int left, int top, int width, int height, char* bitmap, bool space_is_transparent);
  
/* 
get_rand generates a random integer between +/- 30-60.

Parameters:
	None
	
Returns:
	Integer between +/- 30-60.

*/
 int get_rand();