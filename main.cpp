#include <iostream>
#include "cg_pipeline.hpp"
#include "cg_scene.hpp"
#include "cg_canvas.hpp"
#include "cg_bitmap.hpp"

using namespace std;
using namespace cg;

const int SCREEN_X = 800;
const int SCREEN_Y = 600;

int main()
{
	Pipeline ppl;
	Canvas cvs(SCREEN_X, SCREEN_Y);
	Pixel * buf;
	Pixel data[SCREEN_X*SCREEN_Y];
	for ( int i=0; i<SCREEN_Y; i++)
	{
		for ( int j=0; j<SCREEN_X; j++)
		{
			if ( i==100 || i==j || j==300 )
				data[i*SCREEN_X+j] = 0;
			else
				data[i*SCREEN_X+j] = 0xffffff;
		}
	}
	// save pixel array into file
	draw_by_pixel_array( data, SCREEN_X, SCREEN_Y, "demo.bmp");

	return 0;
}
