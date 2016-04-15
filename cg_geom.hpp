#ifndef CG_GEOM_H
#define CG_GEOM_H

#include "cg_math.hpp"

namespace cg
{

class vector3
{
public:
	vector3()
	{
		x=y=z=0;
	}
	vector3( 
		float a_X, 
		float a_Y, 
		float a_Z )
	{
		x = a_X;
		y = a_Y;
		z = a_Z;
	}
	void Set( float a_X, float a_Y, float a_Z ) 
	{
		x = a_X; 
		y = a_Y; 
		z = a_Z; 
	}
	void Normalize() 
	{ 
		float l = 1.0f / Length(); 
		x *= l; 
		y *= l; 
		z *= l; 
	}
	float Length() 
	{ 
		return (float)sqrt( x * x + y * y + z * z ); 
	}
	float SqrLength() 
	{ 
		return x * x + y * y + z * z; 
	}
	float Dot( vector3 a_V ) const
	{ 
		return x * a_V.x + y * a_V.y + z * a_V.z; 
	}
	vector3 Cross( vector3 b ) 
	{ 
		return vector3( 
			y * b.z - z * b.y, 
			z * b.x - x * b.z, 
			x * b.y - y * b.x 
		); 
	}
	void operator += ( const vector3& a_V ) 
	{ 
		x += a_V.x; 
		y += a_V.y; 
		z += a_V.z; 
	}
	void operator += (const vector3* a_V ) 
	{ 
		x += a_V->x; 
		y += a_V->y; 
		z += a_V->z; 
	}
	void operator -= (const vector3& a_V ) 
	{ 
		x -= a_V.x; 
		y -= a_V.y; 
		z -= a_V.z; 
	}
	void operator -= (const vector3* a_V ) 
	{ 
		x -= a_V->x; 
		y -= a_V->y; 
		z -= a_V->z; 
	}
	void operator *= ( float f ) 
	{ 
		x *= f; 
		y *= f; 
		z *= f; 
	}
	void operator *= (const vector3 & a_V ) 
	{ 
		x *= a_V.x; 
		y *= a_V.y; 
		z *= a_V.z;
	}
	void operator *= (const vector3* a_V ) 
	{ 
		x *= a_V->x; 
		y *= a_V->y; 
		z *= a_V->z; 
	}
	vector3 operator- () const 
	{ 
		return vector3( -x, -y, -z ); 
	}
	friend vector3 operator + ( 
		const vector3& v1, 
		const vector3& v2 ) 
	{ 
		return vector3( 
			v1.x + v2.x, 
			v1.y + v2.y, 
			v1.z + v2.z 
		); 
	}
	friend vector3 operator - ( 
		const vector3& v1, 
		const vector3& v2 ) 
	{ 
		return vector3( 
			v1.x - v2.x, 
			v1.y - v2.y, 
			v1.z - v2.z 
		); 
	}
	friend vector3 operator + ( 
		const vector3& v1, 
		vector3* v2 ) 
	{ 
		return vector3( 
			v1.x + v2->x, 
			v1.y + v2->y, 
			v1.z + v2->z 
		); 
	}
	friend vector3 operator - ( 
		const vector3& v1, 
		const vector3* v2 ) 
	{ 
		return vector3( 
			v1.x - v2->x, 
			v1.y - v2->y, 
			v1.z - v2->z 
		); 
	}
	friend vector3 operator * ( 
		const vector3& v, 
		float f ) 
	{ 
		return vector3( v.x * f, v.y * f, v.z * f ); 
	}
	friend vector3 operator * ( 
		const vector3& v1, 
		const vector3& v2 ) 
	{ 
		return vector3( 
			v1.x * v2.x, 
			v1.y * v2.y, 
			v1.z * v2.z 
			); 
	}
	friend vector3 operator * ( 
		float f, 
		const vector3& v ) 
	{ 
		return vector3( 
			v.x * f, 
			v.y * f, 
			v.z * f
		); 
	}
	// copy assignment
	vector3 operator = (const vector3 & v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	float x;
	float y;
	float z;
};


class plane
{
public:
	plane()
	{
		N.Set(0,0,0);
		D = 0;
	};
	plane( vector3 a_Normal, float a_D )
	{
		N.Set( a_Normal.x, a_Normal.y, a_Normal.z );
		D = a_D;
	};
	vector3 N;
	float D;
};


}; // namespace of CG

#endif
