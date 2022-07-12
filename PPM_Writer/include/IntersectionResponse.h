#pragma once
#include <libMath.h>

struct IntersectionResponse
{
	Vector3 HitPos;				//The location in worldspace of the intersection
	Vector3 SurfaceNormal;		//The surface normal at the intersection location
	float distance;				//The distance to the hit location
	Vector3 colour;
};