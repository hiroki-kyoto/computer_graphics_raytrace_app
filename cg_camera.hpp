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
		const vector3 & i_C=vector3(0,0,0), 
		const vector3 & i_X=vector3(1,0,0),
		const vector3 & i_Y=vector3(0,1,0),
		float i_L=5,
		float i_W=8,
		float i_H=6
		) : C(i_C), X(i_X), Y(i_Y), L(i_L), W(i_W), H(i_H)
	{
		if( L<1e-5 || W<1e-5 || H<1e-5 )
		{
			printf( "Error: [Camera] L, W, H should be positive!\n" );
			return;
		}
		if( LENGTH(X)<1e-5 || LENGTH(Y)<1e-5 )
		{
			printf("Error: [Camera] X, Y should be non-zero!\n");
			return;
		}
		if( fabs(X.Dot(Y))>1e-5 )
		{
			printf("Error: [Camera] X, Y NOT ERECTED to each other!\n");
			return;
		}
		// update the rest setting according to N, X, Y, C, W, H, L
		Update();
	}
	// update all parameter of model
	void Update( void )
	{
		// create x axis on the plane given by N
		N = X.Cross(Y);
		X.Normalize();
		Y.Normalize();
		N.Normalize();
		A = C - L * N;
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
		// update basis of canvas
		vector3 oX, oY;
		oX = X;
		oY = Y;
		X = cos( theta ) * oX + sin( theta ) * oY;
		Y = -sin( theta ) * oX + cos( theta ) * oY;
		B = C - 0.5 * W * X - 0.5 * H * Y;
	}
	void LookAt( const vector3 & target )
	{
		// Find out how the Norm of camera rotate by its own axis
		vector3 oN, oX, oY;
		oN = N;
		oX = X;
		oY = Y;
		N = target - C;
		N.Normalize();
		// Get angle rotating around axis [X1]
		float sinBeita = N.Dot( oY );
		float cosBeita = sqrt( 1 - sinBeita * sinBeita );
		float cosAlpha = N.Dot( oN ) / cosBeita;
		float sinAlpha = -N.Dot( oX ) / cosBeita;
		// check correctness
		if( fabs(sinAlpha * sinAlpha + cosBeita * cosBeita - 1.0) < 1e-5 )
		{
			printf( "Error: Bad precision on computing triangle-function!\n");
			return;
		}
		X = cosAlpha * oX + sinAlpha * oN;
		Y = cosBeita * oY - sinBeita * cosAlpha * oN + sinBeita * sinAlpha * X;
		Update();
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
		vector3 center;
		center = C + radius * N;
		vector3 oN, oX, oY;
		oN = N;
		oX = X;
		oY = Y;
		N = cos( alpha ) * oN - sin( alpha ) * oX;
		Y = oY;
		X = Y.Cross( N );
		// second step : beita
		oX = X;
		oY = Y;
		oN = N;
		N = cos( beita ) * oN + sin( beita ) * oY;
		X = oX;
		Y = N.Cross( X );
		N.Normalize();
		C = center - radius * N;
		Update();
	}
	// Look around standing current place
	void LookAround( float alpha, float beita )
	{
		vector3 oX, oY, oN;
		oX = X;
		oY = Y;
		oN = N;
		// first step: horizontally rotating
		N = cos( alpha ) * oN - sin( alpha ) * oX;
		X = cos( alpha ) * oX + sin( alpha ) * oN;
		Y = oY;
		// second step: vertically rotating
		oX = X;
		oY = Y;
		oN = N;
		N = cos( beita ) * oN + sin( beita ) * oY;
		X = oX;
		Y = cos( beita ) * oY - sin( beita ) * oN;
		Update();
	}

	vector3 N;	// norm of plane 
	float	L;	// length of camera
	float	W;	// width of canvas
	float	H;	// height of canvas
	vector3 C;	// center of canvas
	vector3 X;	// x axis on plane
	vector3 Y;	// y axis on plane
	vector3 A;	// origin 
	vector3 B;	// left corner
};

};

#endif
