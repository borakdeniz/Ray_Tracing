#pragma once
#include <libMath.h>

class Material;


struct IntersectionResponse
{
	Vector3 HitPos;				//The location in worldspace of the intersection
	Vector3 SurfaceNormal;		//The surface normal at the intersection location
	float distance;				//The distance to the hit location
	Material* material;			//The material property of the intersected object
};