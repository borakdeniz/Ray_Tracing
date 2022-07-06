#pragma once

#include <iostream>
#include <Vector3.h>
#include <Ray.h>

using ColourRGB = Vector3;

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour) 
{
	//cast float colour values to int for output file
	a_ostream << static_cast<int>(255.999f * a_colour.x) << ' ' <<
				 static_cast<int>(255.999f * a_colour.y) << ' ' <<
				 static_cast<int>(255.999f * a_colour.z) << ' ';
}

ColourRGB RaytoColour(const Ray& a_ray)
{
	return (a_ray.Direction() + 1.f) * 0.5f;
}