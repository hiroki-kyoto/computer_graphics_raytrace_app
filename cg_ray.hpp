#ifndef CG_RAY_H
#define CG_RAY_H

#include "cg_geom.hpp"

namespace cg
{

class Ray
{
public:
	Ray() : 
		m_Origin( vector3( 0, 0, 0 ) ), 
		m_Direction( vector3( 0, 0, 0 ) ) 
	{
		// do nothing
	};
	Ray( vector3& a_Origin, vector3& a_Dir ) : 
		m_Origin( a_Origin ), 
		m_Direction( a_Dir )
	{
		// do nothing
	}
	void SetOrigin( vector3& a_Origin ) 
	{ 
		m_Origin = a_Origin; 
	}
	void SetDirection( vector3& a_Direction ) 
	{ 
		m_Direction = a_Direction; 
	}
	vector3& GetOrigin() 
	{ 
		return m_Origin; 
	}
	vector3& GetDirection() 
	{ 
		return m_Direction; 
	}
private:
	vector3 m_Origin;
	vector3 m_Direction;
};


};

#endif
