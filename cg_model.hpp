#ifndef CG_MODEL_H
#define CG_MODEL_H

#include "string.h"
#include "cg_math.hpp"
#include "cg_geom.hpp"
#include "cg_material.hpp"
#include "cg_ray.hpp"

namespace cg
{

class Primitive
{
public:
	enum
	{
		SPHERE = 1,
		PLANE = 2,
		BOX = 3
	};
	Primitive() : m_Name( 0 ), m_Light( false ) {};
	Material* GetMaterial() 
	{ 
		return &m_Material; 
	}
	void SetMaterial( Material& a_Mat ) 
	{ 
		m_Material = a_Mat; 
	}
	virtual int GetType() = 0;
	virtual int Intersect( Ray& a_Ray, float& a_Dist ) = 0;
	virtual vector3 GetNormal( vector3& a_Pos ) = 0;
	virtual Color GetColor( vector3& ) 
	{ 
		return m_Material.GetColor(); 
	}
	virtual void Light( bool a_Light ) 
	{ 
		m_Light = a_Light; 
	}
	bool IsLight() 
	{ 
		return m_Light; 
	}
	void SetName( const char* a_Name )
	{
		delete m_Name; 
		m_Name = new char[strlen( a_Name ) + 1]; 
		strcpy( m_Name, a_Name );
	}
	char* GetName() 
	{ 
		return m_Name; 
	}
protected:
	Material m_Material;
	char* m_Name;
	bool m_Light;
};


class Sphere : public Primitive
{
public:
	int GetType()
	{ 
		return SPHERE; 
	}
	Sphere( vector3 a_Centre, float a_Radius ) : 
		m_Centre( a_Centre ), m_SqRadius( a_Radius * a_Radius ), 
		m_Radius( a_Radius ), m_RRadius( 1.0f / a_Radius ) {};
	vector3& GetCentre() 
	{ 
		return m_Centre;
	}
	float GetSqRadius() 
	{ 
		return m_SqRadius; 
	}
	int Intersect( Ray& a_Ray, float& a_Dist )
	{
		vector3 v = a_Ray.GetOrigin() - m_Centre;
		float b = -DOT( v, a_Ray.GetDirection() );
		float det = (b * b) - DOT( v, v ) + m_SqRadius;
		int retval = MISS;
		if (det > 0)
		{
			det = sqrtf( det );
			float i1 = b - det;
			float i2 = b + det;
			if (i2 > 0)
			{
				if (i1 < 0) 
				{
					if (i2 < a_Dist) 
					{
						a_Dist = i2;
						retval = INPRIM;
					}
				}
				else
				{
					if (i1 < a_Dist)
					{
						a_Dist = i1;
						retval = HIT;
					}
				}
			}
		}
		return retval;
	}
	vector3 GetNormal( vector3& a_Pos ) 
	{ 
		return (a_Pos - m_Centre) * m_RRadius; 
	}
private:
	vector3 m_Centre;
	float m_SqRadius, m_Radius, m_RRadius;
};


class PlanePrim : public Primitive
{
public:
	int GetType() 
	{ 
		return PLANE; 
	}
	PlanePrim( const vector3 & a_Normal, float a_D ) 
	{
		m_Plane.N = a_Normal;
		m_Plane.D = a_D;
	}
	const vector3 & GetNormal() 
	{ 
		return m_Plane.N;
	}
	float GetD() 
	{ 
		return m_Plane.D; 
	}
	int Intersect( const Ray & a_Ray, float & a_Dist )
	{
		float d = DOT( m_Plane.N, a_Ray.GetDirection() );
		if (d != 0)
		{
			float t = ( m_Plane.D - a_Ray.GetOrigin().Dot( m_Plane.N ) ) / d;
			if ( t > 0 )
			{
				if ( t < a_Dist ) 
				{
					a_Dist = t;
					return HIT;
				}
			}
		}
		return MISS;
	}
	vector3 GetNormal( const vector3 & a_Pos )
	{
		return m_Plane.N;
	}
private:
	plane m_Plane;
};

// box model
class Box : public Primitive
{
public:
	int GetType()
	{
		return BOX;
	}
	Box( const vector3 & centre, const vector3 & dim )
	{
		if( dim.x <= 0 || dim.y <= 0 || dim.z <= 0)
		{
			printf("Error: Dimension of Box should be positive!\n");
			return;
		}
		m_Centre = centre;
		m_Dim = dim;
	}
	const vector3 &  GetCentre()
	{
		return m_Centre;
	}
	const vector3 & GetDim()
	{
		return m_Dim;
	}
	int Intersect()
	{

	}
private:
	vector3 m_Centre, m_Dim;
};


}; // namespace

#endif
