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


class Dielectric : public Material
{
public:
	Dielectric(const float index_of_refraction)
		: index_of_refraction_{ index_of_refraction }
	{	}


	const bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& ray_out) const override
	{
		attenuation = Color{ 1.0f, 1.0f, 1.0f };
		float refraction_ratio{ hit_record.is_front_face_ ? (1.0f / index_of_refraction_) : index_of_refraction_ };

		Vec3 unit_direction{ unit_vector(ray_in.direction()) };
		float cos_theta{ fmin(dot(-unit_direction, hit_record.normal_), 1.0f) };
		float sin_theta{ sqrt(1.0f - cos_theta * cos_theta) };

		bool cannot_refract{ refraction_ratio * sin_theta > 1.0f };
		Vec3 direction{};

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomf())
		{
			direction = reflect(unit_direction, hit_record.normal_);
		}
		else
		{
			direction = refract(unit_direction, hit_record.normal_, refraction_ratio);
		}

		ray_out = Ray(hit_record.point_, direction);
		return true;
	}


private:
	float index_of_refraction_{ 1.0f };

	static float reflectance(float cosine, float refraction_ratio)
	{
		// Schlick's approximation.
		float r0{ (1.0f - refraction_ratio) / (1.0f + refraction_ratio) };
		r0 = r0 * r0;

		return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
	}
};