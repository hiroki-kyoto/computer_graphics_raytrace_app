#include <iostream>
#include <sstream>
#include "cg_pipeline.hpp"
#include "cg_scene.hpp"
#include "cg_canvas.hpp"
#include "cg_bitmap.hpp"

using namespace std;
using namespace cg;

const int SCREEN_X = 800;
const int SCREEN_Y = 600;


// example for bmp image rendering
void test_draw_curve(void)
{
	Pixel data[SCREEN_X*SCREEN_Y];
	for ( int i=0; i<SCREEN_Y; i++)
	{
		for ( int j=0; j<SCREEN_X; j++)
		{
			if ( 500*i-j*j>-500 && 500*i-j*j<500 )
				data[i*SCREEN_X+j] = 0;
			else
				data[i*SCREEN_X+j] = 0xffffff;
		}
	}
	// save pixel array into file
	draw_by_pixel_array( 
		LEFT_BOTTOM, 
		data, 
		SCREEN_X, 
		SCREEN_Y, 
		"demo.bmp"
	);
}

int main()
{
	//test_draw_curve();

	Canvas cvs(SCREEN_X, SCREEN_Y);
	Pixel * buf = cvs.GetBuffer();
	Pipeline ppl = Pipeline();
	// prepare scene to add objects
	ppl.GetScene()->InitScene();
	ppl.SetTarget( cvs.GetBuffer(), SCREEN_X, SCREEN_Y );
	// draw image sequence
	stringstream str_hub;
	int seq_len = 10;

	// after we rotate the camera
	ppl.GetCamera()->Rotate( -0.251 * PI );

	for ( int i=0; i<seq_len; i++)
	{
		str_hub << "seq_" << i << ".bmp";
		ppl.Render();
		draw_by_pixel_array( 
			LEFT_BOTTOM, 
			buf, 
			SCREEN_X, 
			SCREEN_Y, 
			str_hub.str().c_str()
		);
		cout << str_hub.str().c_str() << endl;
		str_hub.str("");
		ppl.GetCamera()->LookAround( 0.02 * PI , 0.0 );
	}
	
	return 0;
}

