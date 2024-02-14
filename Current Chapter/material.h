#pragma once

// Project
#include "ray.h"
#include "interval.h"
#include "vec3.h"
#include "hittable.h"

// Forward declare
//class HitRecord;


class Material
{
public:
	virtual ~Material() = default;

	virtual const bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_out) const = 0;
};


class Lambertian : public Material
{
public:
	Lambertian(const Color& color)
		: albedo_{ color }
	{	}


	const bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_out) const override
	{
		Vec3 scatter_direction{ hit_record.normal_ + random_unit_vector() };

		// Catch rays that are too small / zero.
		if (scatter_direction.near_zero())
		{
			scatter_direction = hit_record.normal_;
		}

		ray_out = Ray{ hit_record.point_, scatter_direction };
		attenuation = albedo_;
		return true;
	}

private:
	Color albedo_{};
};


class Metal : public Material
{
public:
	Metal(const Color& color, const float fuzz)
		: albedo_{ color }
		, fuzz_{ fuzz < 1.0 ? fuzz : 1.0f }
	{	}


	const bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_out) const override
	{
		Vec3 reflected{ reflect(unit_vector(ray_in.direction()), hit_record.normal_) };
		ray_out = Ray{ hit_record.point_, reflected + fuzz_ * random_unit_vector() };
		attenuation = albedo_;
		return (dot(ray_out.direction(), hit_record.normal_) > 0);
	}


private:
	Color albedo_{};
	float fuzz_{ 1.0f };
};