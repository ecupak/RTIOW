#pragma once

// STL
#include <iostream>

// Project
#include "vec3.h"


using Color = Vec3; // Distinguishing alias.


void writeColor(std::ostream& out, Color pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}