#ifndef CG_SCENE_H
#define CG_SCENE_H

#include <iostream>
#include "string.h"
#include "cg_model.hpp"

namespace cg
{

using namespace std;

class Scene
{
public:
	Scene() : m_Primitives( 0 ), m_Primitive( 0 ) {};
	~Scene()
	{
		delete m_Primitive;
	}
	void InitScene()
	{
		m_Primitive = new Primitive*[100];
		// ground plane
		m_Primitive[0] = new PlanePrim( vector3( 0, 1, 0 ), 4.4f );
		m_Primitive[0]->SetName( "plane" );
		m_Primitive[0]->GetMaterial()->SetReflection( 0 );
		m_Primitive[0]->GetMaterial()->SetDiffuse( 1.0f );
		m_Primitive[0]->GetMaterial()->SetColor( Color( 0.4f, 0.3f, 0.3f ) );
		// big sphere
		m_Primitive[1] = new Sphere( vector3( 1, -0.8f, 3 ), 2.5f );
		m_Primitive[1]->SetName( "big sphere" );
		m_Primitive[1]->GetMaterial()->SetReflection( 0.6f );
		m_Primitive[1]->GetMaterial()->SetColor( Color( 0.7f, 0.7f, 0.7f ) );
		// small sphere
		m_Primitive[2] = new Sphere( vector3( -5.5f, -0.5, 7 ), 2 );
		m_Primitive[2]->SetName( "small sphere" );
		m_Primitive[2]->GetMaterial()->SetReflection( 1.0f );
		m_Primitive[2]->GetMaterial()->SetDiffuse( 0.1f );
		m_Primitive[2]->GetMaterial()->SetColor( Color( 0.7f, 0.7f, 1.0f ) );
		// light source 1
		m_Primitive[3] = new Sphere( vector3( 0, 5, 5 ), 0.1f );
		m_Primitive[3]->Light( true );
		m_Primitive[3]->GetMaterial()->SetColor( Color( 0.6f, 0.6f, 0.6f ) );
		// light source 2
		m_Primitive[4] = new Sphere( vector3( 2, 5, 1 ), 0.1f );
		m_Primitive[4]->Light( true );
		m_Primitive[4]->GetMaterial()->SetColor( Color( 0.7f, 0.7f, 0.9f ) );
		// set number of primitives
		m_Primitives = 5;
	}
	int GetNrPrimitives() 
	{ 
		return m_Primitives; 
	}
	Primitive * GetPrimitive( int a_Idx ) 
	{ 
		return m_Primitive[a_Idx]; 
	}
private:
	int m_Primitives;
	Primitive ** m_Primitive;
};

};

#endif
