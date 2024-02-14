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
	int samples_per_pixel_{ 10 };
	int max_depth_{ 10 };

private:
	// Methods.
	void initialize();
	Ray get_ray(int x, int y);
	Vec3 pixel_sample_square();
	Color ray_color(const Ray& ray, int depth, const Hittable& world) const;

	// Properties.
	int image_height_{ 0 };
	Point3 camera_center_{};
	Point3 pixel_00_loc_{};
	Vec3 pixel_delta_u_{};
	Vec3 pixel_delta_v_{};

};