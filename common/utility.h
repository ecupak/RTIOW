#pragma once

// STL
#include <cmath>
#include <limits>
#include <memory>
#include <random>


// Constants

constexpr float inifinity{ std::numeric_limits<float>::infinity() };
constexpr float pi{ 3.1415926535897932385 };

// Functions

inline float radians(float degrees)
{
	return degrees * pi / 180.0f;
}


inline float randomf()
{
	static std::uniform_real_distribution<float> distribution{ 0.0f, 1.0f };
	static std::mt19937 generator{};
	return distribution(generator);
}