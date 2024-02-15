#include "camera.h"

// STL
#include <iostream>

// Includes
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Project
#include "interval.h"
#include "color.h"
#include "material.h"


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
	// Create ray from random spot on defocus disk to pixel center.
	Point3 pixel_center{ pixel_00_loc_ + (x * pixel_delta_u_) + (y * pixel_delta_v_) };
	Point3 pixel_sample{ pixel_center + pixel_sample_square() };
	
	Point3 ray_origin{ (defocus_angle_ <= 0.0f) ? camera_center_ : defocus_disk_sample() };
	Vec3 ray_direction{ pixel_sample - ray_origin };
	return { ray_origin, ray_direction };
}


Point3 Camera::defocus_disk_sample() const
{
	Point3 p{ random_in_unit_disk() };
	return camera_center_ + (p[0] * defocus_disk_u_) + (p[1] * defocus_disk_v_);
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

	camera_center_ = look_from_;

	// Viewport dimensions.	
	float theta{ radians(field_of_view_v_) };
	float h{ tan(theta / 2.0f) };
	float viewport_height{ 2.0f * h * focus_distance_ };
	float viewport_width{ viewport_height * (static_cast<float>(image_width_) / image_height_) };

	// Camera vectors.
	camera_back_ = unit_vector(look_from_ - look_at_);
	camera_right_ = unit_vector(cross(world_up_, camera_back_));
	camera_up_ = cross(camera_back_, camera_right_);

	// Vectors along the viewport edges.
	Vec3 viewport_u{ viewport_width * camera_right_ };
	Vec3 viewport_v{ viewport_height * -camera_up_ };

	// Delta vectors for pixel stride.
	pixel_delta_u_ = viewport_u / image_width_;
	pixel_delta_v_ = viewport_v / image_height_;

	// Find upper-left pixel location.
	Vec3& viewport_upper_left = camera_center_ - focus_distance_ * camera_back_ - viewport_u / 2 - viewport_v / 2;
	pixel_00_loc_ = viewport_upper_left + (pixel_delta_u_ + pixel_delta_v_) / 2.0f;

	// Defocus disk.
	float defocus_radius{ focus_distance_ * tan(radians(defocus_angle_ / 2.0f)) };
	defocus_disk_u_ = camera_right_ * defocus_radius;
	defocus_disk_v_ = camera_up_ * defocus_radius;
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
		Ray scattered_ray{};
		Color attenuation{};

		if (hit_record.material_->scatter(ray, hit_record, attenuation, scattered_ray))
		{
			return attenuation * ray_color(scattered_ray, depth - 1, world);
		}
		return { 0.0f, 0.0f, 0.0f };
	}

	// Missed, get background color.
	Vec3 unitDirection{ unit_vector(ray.direction()) };
	float t{ (unitDirection.y() + 1.0f) / 2 };

	static Color white{ 1.0f, 1.0f, 1.0f };
	static Color skyblue{ 0.5f, 0.7f, 1.0f };

	return { (white * (1.0f - t)) + (skyblue * t) };
}