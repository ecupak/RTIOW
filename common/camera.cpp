#include "camera.h"

// STL
#include <iostream>

// Includes
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Project
#include "interval.h"
#include "color.h"


void Camera::render(const Hittable& world, const char* image_output_filepath)
{
	static bool is_initialized{ false };

	if (!is_initialized)
	{
		initialize();

		is_initialized = true;
	}

	using channel = char;

	int channel_count{ 3 };
	int stride_in_bytes{ channel_count * image_width_ };
	channel* png_data{ new channel[image_width_ * image_height_ * channel_count] };

	int pixel_index = 0;

	for (int y = 0; y < image_height_; ++y)
	{
		std::clog << "\rScanlines remaining: " << (image_height_ - y) << ' ' << std::flush;

		for (int x = 0; x < image_width_; ++x)
		{
			Color pixel_color{ 0.0f, 0.0f, 0.0f };
			
			for (int sample = 0; sample < samples_per_pixel_; ++sample)
			{
				Ray ray{ get_ray(x, y) };
				pixel_color += ray_color(ray, max_depth_, world);
			}

			// Adjust pixel color by sample size.
			float scale{ 1.0f / samples_per_pixel_ };
			pixel_color *= scale;

			// Move into gamma space.
			for (int i = 0; i < 3; ++i)
			{
				pixel_color[i] = linear_to_gamma(pixel_color[i]);
			}

			// Store color data of pixel.
			static const Interval intensity{ 0.0f, 0.999f };
			png_data[pixel_index + 0] = static_cast<channel>(256 * intensity.clamp(pixel_color.x()));
			png_data[pixel_index + 1] = static_cast<channel>(256 * intensity.clamp(pixel_color.y()));
			png_data[pixel_index + 2] = static_cast<channel>(256 * intensity.clamp(pixel_color.z()));

			pixel_index += channel_count;
		}
	}

	std::clog << "\rDone                      \n";
	
	if (strlen(image_output_filepath) > 0)
	{
		stbi_write_png(image_output_filepath, image_width_, image_height_, channel_count, png_data, stride_in_bytes);
	}

	delete[] png_data;

}

Ray Camera::get_ray(int x, int y)
{
	// Create ray from camera to pixel center.
	Point3 pixel_center{ pixel_00_loc_ + (x * pixel_delta_u_) + (y * pixel_delta_v_) };
	Point3 pixel_sample{ pixel_center + pixel_sample_square() };
	
	Vec3 camera_to_pixel{ pixel_sample - camera_center_ };
	return { camera_center_, camera_to_pixel };
}


Vec3 Camera::pixel_sample_square()
{
	// Return random point within square surrounding pixel (pixel center lies on the half integer).
	float px{ randomf() - 0.5f };
	float py{ randomf() - 0.5f };

	return { (px * pixel_delta_u_) + (py * pixel_delta_v_) };
}


void Camera::initialize()
{
	// Calculate image height (must be at least 1).
	image_height_ = static_cast<int>(image_width_ / aspect_ratio_);
	image_height_ = (image_height_ < 1) ? 1 : image_height_;

	// Camera.
	float focal_length{ 1.0f };
	float viewport_height{ 2.0f };
	float viewport_width{ viewport_height * (static_cast<float>(image_width_) / image_height_) };	

	// Vectors along the viewport edges.
	Vec3 viewport_u{ viewport_width, 0.0f, 0.0f };
	Vec3 viewport_v{ 0.0f, -viewport_height, 0.0f };

	// Delta vectors for pixel stride.
	pixel_delta_u_ = viewport_u / image_width_;
	pixel_delta_v_ = viewport_v / image_height_;

	// Find upper-left pixel location.
	Vec3& viewport_upper_left = camera_center_ - viewport_u / 2 - viewport_v / 2 - Vec3(0.0f, 0.0f, focal_length);
	pixel_00_loc_ = viewport_upper_left + (pixel_delta_u_ + pixel_delta_v_) / 2.0f;
}


Color Camera::ray_color(const Ray& ray, int depth, const Hittable& world) const
{
	HitRecord hit_record;

	// Reached max bounces. Return no light.
	if (depth <= 0)
	{
		return { 0.0f, 0.0f, 0.0f };
	}

	// Check for hit (bounce ray).
	if (world.hit(ray, Interval{ 0.001f, inifinity }, hit_record))
	{
		Vec3 direction{ hit_record.normal + random_unit_vector() };
		return { ray_color(Ray{hit_record.point, direction}, depth - 1, world) / 2.0f };
	}

	// Missed, get background color.
	Vec3 unitDirection{ unit_vector(ray.direction()) };
	float t{ (unitDirection.y() + 1.0f) / 2 };

	static Color white{ 1.0f, 1.0f, 1.0f };
	static Color skyblue{ 0.5f, 0.7f, 1.0f };

	return { (white * (1.0f - t)) + (skyblue * t) };
}