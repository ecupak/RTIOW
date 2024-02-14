#pragma once

// STL
#include <cmath>
#include <limits>
#include <memory>


// Constants

constexpr float inifinity{ std::numeric_limits<float>::infinity() };
constexpr float pi{ 3.1415926535897932385 };

// Functions

inline float radians(float degrees)
{
	return degrees * pi / 180.0f;
}