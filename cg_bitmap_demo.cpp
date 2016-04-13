#include <stdio.h>
#include <math.h>

#include "cg_bitmap.hpp"

// ASSURE [MAT] IS EMPTY BY DEFAULT
void create_matrix(byte*** mat, unsigned long width, unsigned long height)
{
	(*mat) = (byte**)malloc(sizeof(byte*)*height);
	
	for(unsigned long i=0;i<height;i++)
	{
		(*mat)[i] = (byte*)malloc(sizeof(byte)*width);
		memset((*mat)[i], 0, sizeof(byte)*width);
	}
}

void free_matrix(byte** mat, unsigned long height)
{
	for(unsigned long i=0;i<height;i++)
	{
		free(mat[i]);
	}
	free(mat);
}

#endif

void draw_gray_image_from_matrix_data(void)
{
	byte** mat;
	
	unsigned long width = 80;
	unsigned long height  = 60;
	
	// col = width; raw = height
	create_matrix(&mat, width, height);

	// modify the matrix
	for(unsigned long j=0;j<width;j++)
	{
		mat[0][j] = 0x33;
	}
	
	for(unsigned long i=1;i<height;i++)
	{
		for(unsigned long j=0;j<width;j++)
		{
			mat[i][j] = 0xAA;
		}
	}
	
	save_data_as_bitmap(mat, width, height, "gray_demo.bmp");
	free_matrix(mat, height);
	printf("Gray Image Drawn from Matrix Data Done.\n");

}

void draw_rgb_image_from_pixel_array(void)
{
	const int width = 800;
	const int height = 600;
	pixel data[width*height];
	for(int i=0; i<width*height; i++)
		data[i] = (i%256) + ((3*i%256)<<8) + ((5*i%256)<<16);
	draw_by_pixel_array(data, width, height, "rgb_demo.bmp");
	printf("RGB Image Drawn from Pixel Array Done.\n");
}

int main(int argc, const char** argv)
{
	draw_rgb_image_from_pixel_array();
	draw_gray_image_from_matrix_data();

	return 0;
}



