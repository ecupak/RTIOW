#pragma once

// Project
#include "vec3.h"


class Ray {
public:
	// Ctors.
	Ray() = default;

	Ray(const Point3& origin, const Vec3& direction)
		: origin_{ origin }
		, direction_{ direction }
	{	}


	// Methods.
	Point3 at(float t)
	{
		return Point3{ origin_ + (direction_ * t) };
	}


	// Getters.
	Point3 origin() const
	{
		return origin_;
	}

	Vec3 direction() const
	{
		return direction_;
	}


private:
	Point3 origin_{ 0.0f, 0.0f, 0.0f };
	Vec3 direction_{ 0.0f, 0.0f, 0.0f };

};