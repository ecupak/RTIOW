#pragma once

// Project
#include "hittable.h"
#include "ray.h"
#include "vec3.h"


class Sphere : public Hittable
{
public:
	Sphere(Point3 center, float radius)
		: center_{ center }
		, radius_{ radius }
	{	}

	const bool hit(const Ray& ray, float ray_Tmin, float ray_Tmax, HitRecord& hit_record) const override
	{
		Vec3 center_to_origin = (ray.origin() - center_);

		float a = ray.direction().length_squared();
		float half_b = dot(ray.direction(), center_to_origin);
		float c = center_to_origin.length_squared() - pow(radius_, 2.0f);

		float discriminant = pow(half_b, 2.0f) - a * c;

		// Ray missed.
		if (discriminant < 0)
		{
			return false;
		}

		// Find nearest root to ray origin within range.
		float sqrt_discriminant{ sqrt(discriminant) };
		float root{ (-half_b - sqrt_discriminant) / a};

		if (root <= ray_Tmin || root >= ray_Tmax)
		{
			root = (-half_b + sqrt_discriminant) / a;

			if (root <= ray_Tmin || root >= ray_Tmax)
			{
				return false;
			}
		}

		// If root is in range, store data in hit record.
		hit_record.t = root;
		hit_record.point = ray.at(root);
		Vec3 outward_normal{ (hit_record.point - center_) / radius_ };
		hit_record.setFaceNormal(ray, outward_normal);

		return true;
	}

private:
	Point3 center_{};
	float radius_{ 1.0f };
};
