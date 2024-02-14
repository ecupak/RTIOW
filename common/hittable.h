#pragma once

// Project
#include "ray.h"
#include "vec3.h"
#include "interval.h"


class HitRecord 
{
public:
	Point3 point{};
	Vec3 normal{};
	float t{ 0.0f };
	bool is_front_face{ false };

	void setFaceNormal(const Ray& ray, const Vec3& outward_normal)
	{
		// Sets the hit record normal vector.
		// NOTE: the parameter `outward_normal` is assumed to have unit length.

		is_front_face = dot(ray.direction(), outward_normal) < 0.0f;
		normal = is_front_face ? outward_normal : -outward_normal;
	}
};


class Hittable {
public:
	virtual ~Hittable() = default;


	virtual const bool hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const = 0;
};