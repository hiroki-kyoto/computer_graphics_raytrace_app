#ifndef CG_CAMERA_H
#define CG_CAMERA_H

#include "math.h"
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
		if ( L <= 0 || W <= 0 || H <= 0 )
		{
			printf( "Error: Camera Length, width height should be positive!\n" );
			return;
		}
		Update();
	}
	// update all parameter of model
	void Update( void )
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
		X = cos( theta ) * X + sin( theta ) * Y;
		Y = -sin( theta ) * X + cos( theta ) * Y;
		B = C - 0.5 * W * X - 0.5 * H * Y;
	}
	// method to operate this camera
	void Move( const vector3 & v )
	{
		// update origin point and canvas center and base
		A += v;
		B += v;
		C += v;
	}
	void Rotate( float theta )
	{
		T += theta;
		// update basis of canvas
		X = cos ( theta ) * X + sin ( theta ) * Y;
		Y = -sin( theta ) * X + cos ( theta ) * Y;
		B = C - 0.5 * W * X - 0.5 * H * Y;
	}
	void LookAt( const vector3 & target )
	{
		N = target - A;
		Update ();
	}
	void Pull( float d )
	{
		if ( d <= 0 )
		{
			printf( "Error: Camera.Pull argument should be positive!\n" );
			return;
		}
		// just move Origin
		L += d;
		A = C - L * N;
	}
	void Push( float d )
	{
		if ( d <= 0 )
		{
			printf( "Error: Camera.Pull argument should be positive!\n" );
			return;
		}
		// just move Origin
		L -= d;
		if ( L<=0 )
		{
			printf( " Error: Camera.Length should be positive!\n");
			return;
		}
		A = C - L * N;
	}
	// once looked at the object, use CircleAround to 
	void CircleAround( float radius, float alpha, float beita )
	{
		if ( radius <= 0 )
		{
			printf( "Error: Radius of CircleAround should be positive!\n" );
			return;
		}
		// update Norm of canvas
		N = cos( beita ) *
			( cos( alpha ) * N - sin( alpha ) * X ) - 
			sin( beita ) * Y;
		A = ( 0 - radius - L ) * N;
		Update();
	}
	// Look around standing current place
	void LookAround( float alpha, float beita )
	{
		
	}
private:
	vector3 A;	// origin 
	vector3 N;	// norm of plane 
	float	L;	// length of camera
	float	W;	// width of canvas
	float	H;	// height of canvas
	float	T;	// rotate angle
	vector3 C;	// center of canvas
	vector3 X;	// x axis on plane
	vector3 Y;	// y axis on plane
	vector3 B;	// left corner
};

};

#endif
