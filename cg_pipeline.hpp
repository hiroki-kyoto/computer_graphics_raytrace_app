#ifndef CG_PIPELINE_H
#define CG_PIPELINE_H

#include "cg_model.hpp"
#include "cg_ray.hpp"
#include "cg_scene.hpp"
#include "cg_camera.hpp"

namespace cg
{

class Pipeline
{
public:
	Pipeline()
	{
		m_Scene = new Scene();
		m_Camera = new Camera();
		m_LastRow = new Primitive*[m_Width];
		memset( m_LastRow, 0, m_Width * sizeof(Primitive*) );
	}
	~Pipeline()
	{
		delete m_Scene;
		delete m_Camera;
		delete m_LastRow;
	}
	void SetTarget( Pixel* a_Dest, int a_Width, int a_Height )
	{
		// set pixel buffer address & size
		m_Dest = a_Dest;
		m_Width = a_Width;
		m_Height = a_Height;
	}
	Scene * GetScene() 
	{ 
		return m_Scene; 
	}
	Camera * GetCamera()
	{
		return m_Camera;
	}
	Primitive* Raytrace( 
		Ray& a_Ray, 
		Color& a_Acc, 
		int a_Depth, 
		float a_RIndex, 
		float& a_Dist 
		)
	{
		if (a_Depth > TRACEDEPTH) return 0;
		// trace primary ray
		a_Dist = 1000000.0f;
		vector3 pi;
		Primitive* prim = 0;
		int result;
		// find the nearest intersection
		for ( int s = 0; s < m_Scene->GetPrimCount(); s++ )
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
			for ( int l = 0; l < m_Scene->GetPrimCount(); l++ )
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
	// RENDER THE SCENE ONTO THE CANVAS
	void Render()
	{
		// set first line to draw to
		int beginX = 0;
		int beginY = 0;
		int endX = m_Width;
		int endY = m_Height - 10;
		float ratioX = m_Camera->W / m_Width;
		float ratioY = m_Camera->H / m_Height;
		// last primitive that be hit
		Primitive* lastPrim = 0;
		vector3 incX = ratioX * m_Camera->X;
		vector3 incY = ratioY * m_Camera->Y;
		vector3 posY = m_Camera->B + beginY * incY;
		vector3 posX;
		int cposX;
		int cposY = beginY * m_Width;
		for ( int y = beginY; y < endY; y ++ )
		{
			posX = posY + beginX * incX;
			cposX = cposY + beginX;
			for ( int x = beginX; x < endX; x ++ )
			{
				// fire primary ray
				Color acc( 0, 0, 0 );
				vector3 dir = posX - m_Camera->A;
				NORMALIZE( dir );
				Ray r( posX, dir );
				float dist;
				Primitive * prim = Raytrace( r, acc, 1, 1.0f, dist );
				int red = (int)(acc.r * 256);
				int green = (int)(acc.g * 256);
				int blue = (int)(acc.b * 256);
				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;
				m_Dest[cposX] = (red << 16) + (green << 8) + blue;
				posX += incX;
				cposX ++;
			}
			posY += incY;
			cposY += m_Width;
		}
	}
protected:
	Camera * m_Camera;			// camera in world 
	Scene * m_Scene;				// scene to render
	Pixel * m_Dest;				// bitmap pixel array
	int m_Width, m_Height;		// width and height of canvas in pixel
	Primitive ** m_LastRow;		// objects that hits
};

};


#endif
