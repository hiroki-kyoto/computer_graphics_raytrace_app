#ifndef CG_MATH_H
#define CG_MATH_H

#include "math.h"
#include "stdlib.h"

namespace cg
{

typedef unsigned int Pixel;

inline float Rand( float a_Range ) 
{ 
	return ((float)rand() / RAND_MAX) * a_Range; 
}

#define DOT(A,B)		(A.x*B.x+A.y*B.y+A.z*B.z)
#define NORMALIZE(A)	\
	{\
		float l=1/sqrtf(A.x*A.x+A.y*A.y+A.z*A.z);\
		A.x*=l;\
		A.y*=l;\
		A.z*=l;\
	}
#define LENGTH(A)		(sqrtf(A.x*A.x+A.y*A.y+A.z*A.z))
#define SQRLENGTH(A)	(A.x*A.x+A.y*A.y+A.z*A.z)
#define SQRDISTANCE(A,B) (\
	(A.x-B.x)*(A.x-B.x)+\
	(A.y-B.y)*(A.y-B.y)+\
	(A.z-B.z)*(A.z-B.z))

#define EPSILON			0.0001f
#define TRACEDEPTH		6
#define PI				3.141592653589793238462f

#define HIT		 1		// Ray hit primitive
#define MISS	 0		// Ray missed primitive
#define INPRIM	-1		// Ray started inside primitive

};

#endif