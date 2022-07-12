#pragma once

#include <iostream>
#include <Vector3.h>
#include <Ray.h>

using ColourRGB = Vector3;

void WriteColourRGB(std::ostream& a_ostream, ColourRGB a_colour);


ColourRGB RaytoColour(const Ray& a_ray);
