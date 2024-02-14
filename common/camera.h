#pragma once

// Project
#include "vec3.h"
#include "hittable.h"
#include "ray.h"


class Camera
{
public:
	// Ctor.
	Camera() = default;


	// Methods.
	void render(const Hittable& world, const char* image_output_filepath = "");


	// Properties.
	float aspect_ratio_{ 1.0f };
	int image_width_{ 100 };

private:
	// Methods.
	void initialize();
	Color rayColor(const Ray& ray, const Hittable& world) const;

	// Properties.
	int image_height_{ 0 };
	Point3 camera_center_{};
	Point3 pixel_00_loc_{};
	Vec3 pixel_delta_u_{};
	Vec3 pixel_delta_v_{};

};