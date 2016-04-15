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
	Scene() 
	{
		m_PrimCap = 100;
		m_PrimCount = 0;
		m_PrimList = new Primitive * [ m_PrimCap ];
	};
	~Scene()
	{
		delete m_PrimList;
	}
	void InitScene()
	{
		// light source 1
		int pid = AddPrimitive( new Sphere( vector3( 0.0, 2.0, -1.0 ), 0.1 ) );
		if ( pid < 0 )
			return;
		m_PrimList[pid]->Light( true );
		m_PrimList[pid]->GetMaterial()->SetColor( Color( 0.8f, 0.8f, 0.8f ) );

		// ground
		pid = AddPrimitive( new PlanePrim( vector3( 0, 1, 0 ), -5 ) );
		if ( pid < 0 )
			return;
		m_PrimList[pid]->SetName( "GROUND" );
		m_PrimList[pid]->GetMaterial()->SetReflection( 0.0 );
		m_PrimList[pid]->GetMaterial()->SetDiffuse( 0.5 );
		m_PrimList[pid]->GetMaterial()->SetColor( Color( 1.0f, 0.0f, 0.0f ) );

		// wall
		pid = AddPrimitive( new PlanePrim( vector3( 0, 0, -1 ), -8 ) );
		if ( pid < 0 )
			return;
		m_PrimList[pid]->SetName( "WALL" );
		m_PrimList[pid]->GetMaterial()->SetReflection( 0.0 );
		m_PrimList[pid]->GetMaterial()->SetDiffuse( 0.5 );
		m_PrimList[pid]->GetMaterial()->SetColor( Color( 0.0f, 0.0f, 1.0f ) );


		// sphere 001
		pid = AddPrimitive( new Sphere( vector3( 0.0f, 0.0f, 3.0f ), 1.0f ) );
		if( pid < 0 )
			return;
		m_PrimList[pid]->SetName( "GREEN BALL" );
		m_PrimList[pid]->Light( false );
		m_PrimList[pid]->GetMaterial()->SetReflection( 0.5 );
		m_PrimList[pid]->GetMaterial()->SetDiffuse( 0.8 );
		m_PrimList[pid]->GetMaterial()->SetColor( Color( 0.0f, 1.0f, 0.0f ) );

	}
	int GetPrimCount()
	{
		return m_PrimCount; 
	}
	Primitive * GetPrimitive( int a_Idx )
	{
		return m_PrimList[a_Idx]; 
	}
	int AddPrimitive( Primitive * prim )
	{
		if ( m_PrimCount == m_PrimCap )
		{
			printf( "Error: object count exceeding capcity of scene! \n" );
			return -1;
		}
		m_PrimList[m_PrimCount] = prim;
		m_PrimCount ++;
		return m_PrimCount - 1;
	}
private:
	int m_PrimCount;			// count of primitives
	int m_PrimCap;				// capcity of primitives
	Primitive ** m_PrimList;	// primitive list
};

};

#endif
