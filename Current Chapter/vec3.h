#pragma once

// STL
#include <cmath>
#include <iostream>

// Project
#include "utility.h"


class Vec3 
{
public:
	float e[3];

	// Ctors.
	Vec3()
		: e{ 0.0f, 0.0f, 0.0f }
	{	}

	Vec3(float e0, float e1, float e2)
		: e{ e0, e1, e2 }
	{	}


	// Methods.
	float length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	float length() const
	{
		return std::sqrt(length_squared());
	}
	
	static Vec3 random()
	{
		return { randomf(), randomf(), randomf() };
	}

	static Vec3 random(float min, float max)
	{
		return { randomf(min, max), randomf(min, max), randomf(min, max) };
	}
	
	const bool near_zero() const
	{
		static float threshhold{ 1e-8 };
		return (fabs(e[0]) < threshhold) && (fabs(e[1]) < threshhold) && (fabs(e[2]) < threshhold);
	}


	// Primary components.
	float x() const
	{
		return e[0];
	}

	float y() const
	{
		return e[1];
	}

	float z() const
	{
		return e[2];
	}

	// Getters.
	Vec3 operator-() const
	{
		return Vec3(-e[0], -e[1], -e[2]);
	}

	float operator[](int i) const
	{
		return e[i];
	}

	float& operator[](int i)
	{
		return e[i];
	}

	// Arithmetic.
	Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];

		return *this;
	}

	Vec3& operator*=(float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	Vec3& operator/=(float t)
	{
		return *this *= (1 / t);
	}

};


// Distinguishing aliases.
using Point3 = Vec3; 
using Color = Vec3;	


// Vector utility functions.

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3{ u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] };
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3{ u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] };
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3{ u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] };
}

inline Vec3 operator*(const float t, const Vec3& v)
{
	return Vec3{ t * v.e[0], t * v.e[1], t * v.e[2] };
}

inline Vec3 operator*(const Vec3& v, const float t)
{
	return t * v;
}

inline Vec3 operator/(const Vec3& v, const float t)
{
	return (1 / t) * v;
}

inline float dot(const Vec3& u, const Vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3{
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]
	};
}

inline Vec3 unit_vector(Vec3 v)
{
	return v / v.length();
}

inline Vec3 random_in_unit_sphere()
{
	while (true)
	{
		Vec3 p{ Vec3::random(-1.0f, 1.0f) };
		if (p.length_squared() < 1.0f)
		{
			return p;
		}
	}
}

inline Vec3 random_unit_vector()
{
	return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal)
{
	Vec3 on_unit_sphere{ random_unit_vector() };

	if (dot(on_unit_sphere, normal) > 0.0f)
	{
		return on_unit_sphere;
	}
	else
	{
		return -on_unit_sphere;
	}
}

inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - 2.0f * dot(v, n) * n;
}