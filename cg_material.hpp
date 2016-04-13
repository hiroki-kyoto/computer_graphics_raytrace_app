#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H

#include "cg_math.hpp"
#include "cg_geom.hpp"

namespace cg
{

// definition of color class
class Color : public vector3
{
public:
	Color() : r(x), g(y), b(z)
	{
		r = g = b = 0;
	}
	Color(float _r, float _g, float _b) : r(x), g(y), b(z)
	{
		r = _r;
		g = _g;
		b = _b;
	}
	// copy assignment
	Color operator = (const Color & c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		return *this;
	} // note: reference variables cannot be reassigned
	float & r;
	float & g;
	float & b;
};


class Material
{
public:
	Material() :
		m_Color( Color( 0.2f, 0.2f, 0.2f ) ),
		m_Refl( 0 ), m_Diff( 0.2f ) {}
	void SetColor( Color a_Color ) 
	{ 
		m_Color = a_Color; 
	}
	Color& GetColor()
	{ 
		return m_Color; 
	}
	void SetDiffuse( float a_Diff ) 
	{ 
		m_Diff = a_Diff; 
	}
	void SetReflection( float a_Refl ) 
	{ 
		m_Refl = a_Refl; 
	}
	float GetSpecular() 
	{ 
		return 1.0f - m_Diff; 
	}
	float GetDiffuse() 
	{ 
		return m_Diff; 
	}
	float GetReflection() 
	{ 
		return m_Refl; 
	}
private:
	Color m_Color;
	float m_Refl;
	float m_Diff;
};

};

#endif
