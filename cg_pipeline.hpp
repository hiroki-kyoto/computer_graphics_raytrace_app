#ifndef CG_PIPELINE_H
#define CG_PIPELINE_H

#include "cg_model.hpp"
#include "cg_ray.hpp"
#include "cg_scene.hpp"

namespace cg
{

class Pipeline
{
public:
	Pipeline()
	{
		m_Scene = new Scene();
		m_LastRow = NULL;
	}
	~Pipeline()
	{
		delete m_Scene;
		delete m_LastRow;
	}
	void SetTarget( Pixel* a_Dest, int a_Width, int a_Height )
	{
		// set pixel buffer address & size
		m_Dest = a_Dest;
		m_Width = a_Width;
		m_Height = a_Height;
	}
	Scene* GetScene() 
	{ 
		return m_Scene; 
	}
	Primitive* Raytrace( 
		Ray& a_Ray, 
		Color& a_Acc, 
		int a_Depth, 
		float a_RIndex, 
		float& a_Dist )
	{
		if (a_Depth > TRACEDEPTH) return 0;
		// trace primary ray
		a_Dist = 1000000.0f;
		vector3 pi;
		Primitive* prim = 0;
		int result;
		// find the nearest intersection
		for ( int s = 0; s < m_Scene->GetNrPrimitives(); s++ )
		{
			Primitive* pr = m_Scene->GetPrimitive( s );
			int res = pr->Intersect( a_Ray, a_Dist );
			if (res) 
			{
				prim = pr;
				result = res; 
				// 0 = miss, 1 = hit, -1 = hit from inside primitive
			}
		}
		// no hit, terminate ray
		if (!prim) return 0;
		// handle intersection
		if (prim->IsLight())
		{
			// we hit a light, stop tracing
			a_Acc = Color( 1, 1, 1 );
		}
		else
		{
			// determine color at point of intersection
			pi = a_Ray.GetOrigin() + a_Ray.GetDirection() * a_Dist;
			// trace lights
			for ( int l = 0; l < m_Scene->GetNrPrimitives(); l++ )
			{
				Primitive* p = m_Scene->GetPrimitive( l );
				if (p->IsLight()) 
				{
					Primitive* light = p;
					// calculate diffuse shading
					vector3 L = ((Sphere*)light)->GetCentre() - pi;
					NORMALIZE( L );
					vector3 N = prim->GetNormal( pi );
					if (prim->GetMaterial()->GetDiffuse() > 0)
					{
						float dot = DOT( N, L );
						if (dot > 0)
						{
							float diff = dot *
								prim->GetMaterial()->GetDiffuse();
							// add diffuse component to ray color
							a_Acc += diff * 
								prim->GetMaterial()->GetColor() * 
								light->GetMaterial()->GetColor();
						}
					}
				}
			}
		}
		// return pointer to primitive hit by primary ray
		return prim;
	}
	void InitRender()
	{
		// screen plane in world space coordinates
		m_WX1 = -4, m_WX2 = 4, m_WY1 = 3, m_WY2 = -3;
		// calculate deltas for interpolation
		m_DX = (m_WX2 - m_WX1) / m_Width;
		m_DY = (m_WY2 - m_WY1) / m_Height;
		
		// allocate space to store pointers to primitives for previous line
		delete m_LastRow;
		m_LastRow = new Primitive*[m_Width];
		memset( m_LastRow, 0, m_Width * 4 );
	}
	// MOVE CANVAS AND EYE IN WORLD SPACE
	void MoveCamera(vector3 & v)
	{
		m_WX1 += v.x;
		m_WX2 += v.x;
		m_WY1 += v.y;
		m_WY2 += v.y;
		m_WZ1 += v.z;
		m_WZ2 += v.z;
		// change 
	}
	// ROTATE CAMERA
	// RENDER THE SCENE ONTO THE CANVAS
	bool Render()
	{
		// set firts line to draw to
		m_CurrLine = 10;
		// set pixel buffer address of first pixel
		m_PPos = m_CurrLine * m_Width;
		// set the current ray origin position
		m_SY = m_WY1 + m_CurrLine * m_DY;

		// render scene
		vector3 o( 0, 0, -5 );
		// reset last found primitive pointer
		Primitive* lastprim = 0;
		// render remaining lines
		for ( int y = m_CurrLine; y < m_Height; y++ )
		{
			m_SX = m_WX1;
			// render pixels for current line
			for ( int x = 0; x < m_Width; x++ )
			{
				// fire primary ray
				Color acc( 0, 0, 0 );
				vector3 dir = vector3( m_SX, m_SY, m_SZ ) - o;
				NORMALIZE( dir );
				Ray r( o, dir );
				float dist;
				Primitive* prim = Raytrace( r, acc, 1, 1.0f, dist );
				int red = (int)(acc.r * 256);
				int green = (int)(acc.g * 256);
				int blue = (int)(acc.b * 256);
				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;
				m_Dest[m_PPos++] = (red << 16) + (green << 8) + blue;
				m_SX += m_DX;
			}
			m_SY += m_DY;
		}
		// all done
		return true;
	}
protected:
	// renderer data
	Camera camera;				// camera in world
	float m_WX1, m_WY1, m_WZ1; 
	float m_WX2, m_WY2, m_WZ2;
	float m_DX, m_DY, m_DZ;		// delta increment
	float m_SX, m_SY, m_SZ;		// ray current tracing position 
	Scene* m_Scene;
	Pixel* m_Dest;
	int m_Width, m_Height, m_CurrLine, m_PPos;
	Primitive** m_LastRow;
};

};


#endif
