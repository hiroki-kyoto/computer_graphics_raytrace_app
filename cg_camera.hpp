#ifndef CG_CAMERA_H
#define CG_CAMERA_H

#include "cg_geom.hpp"

namespace cg
{

class Camera
{
public:
	Camera (
		const vector3 & i_A, 
		const vector3 & i_N, 
		float i_L=5,
		float i_W=8,
		float i_H=6,
		float i_T=0) : A(i_A), N(i_N), L(i_L), W(i_W), H(i_H), T(i_T)
	{
		// create x axis on the plane given by N
		if( N.x != 0 )
		{
			X.x = -( N.y + N.z ) / N.x;
			X.y = 1.0;
			X.z = 1.0;
		}
		else if( N.y != 0 )
		{
			X.y = -( N.x + N.z ) / N.y;
			X.x = 1.0;
			X.z = 1.0;
		}
		else if( N.z != 0 )
		{
			X.z = -( N.x + N.y ) / N.z;
			X.x = 1.0;
			X.y = 1.0;
		}
		else
		{
			printf("Error: Norm of plane should not be (0,0,0)!\n");
			return;
		}
		// get another axis based on X.*Y=0 and X.*N = 0 and Y.*N = 0
		Y = N.Cross( X );
		N.Normalize();
		X.Normalize();
		Y.Normalize();
		C = A + L * N;
		
	}
	vector3 A;	// origin 
	vector3 N;	// norm of plane 
	float	L;	// length of camera
	float	W;	// width of canvas
	float	H;	// height of canvas
	float	T;	// rotate angle
	vector3 C;	// center of canvas
	vector3 X;	// x axis on plane
	vector3 Y;	// y axis on plane
	// method to operate this camera
	void Move( vector3 & v )
	{
		A += v;
		B += v;
	}
	void 
};

};

#endif
