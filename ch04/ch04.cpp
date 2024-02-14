#include "ch04.h"

// STL
#include <iostream>

// Includes
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Project
#include "vec3.h"
#include "ray.h"



Color rayColor(const Ray& ray)
{
	Vec3 unitDirection{ unit_vector(ray.direction()) };
	float t{ (unitDirection.y() + 1.0f) / 2 };
	
	static Color white{ 1.0f, 1.0f, 1.0f };
	static Color skyblue{ 0.5f, 0.7f, 1.0f };

	return (white * (1.0f - t)) + (skyblue * t);
}


int main()
{
	// IMAGE

	float aspect_ratio{ 16.0f / 9.0f };
	int image_width{ 400 };

	// Calculate image height (must be at least 1).
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera.
	float focal_length{ 1.0f };
	float viewport_height{ 2.0f };
	float viewport_width{ viewport_height * (static_cast<float>(image_width) / image_height) };
	Point3 camera_center{};

	// Vectors along the viewport edges.
	Vec3 viewport_u{ viewport_width, 0.0f, 0.0f };
	Vec3 viewport_v{ 0.0f, -viewport_height, 0.0f };

	// Delta vectors for pixel stride.
	Vec3 pixel_delta_u{ viewport_u / image_width };
	Vec3 pixel_delta_v{ viewport_v / image_height };

	// Find upper-left pixel location.
	Point3 viewport_upper_left{ camera_center - viewport_u / 2 - viewport_v / 2 - Vec3(0.0f, 0.0f, focal_length) };
	Point3 pixel_00_loc{ viewport_upper_left + (pixel_delta_u + pixel_delta_v) / 2.0f };


	// RENDER

	using channel = char;
	
	int channel_count{ 3 };
	int stride_in_bytes{ channel_count * image_width };
	channel* png_data{ new channel[image_width * image_height * channel_count] };
	
	int pixel_index = 0;

	for (int y = 0; y < image_height; ++y)
	{
		std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;

		Point3 pixel_row{ pixel_00_loc + (y * pixel_delta_v) };

		for (int x = 0; x < image_width; ++x)
		{
			// Create ray from camera to pixel center.
			Point3 pixel_center{ pixel_row + (x * pixel_delta_u) };
			Vec3 camera_to_pixel{ pixel_center - camera_center };
			Ray ray{ camera_center, camera_to_pixel };

			// Get color ray intersects.
			Color pixel_color{ rayColor(ray) };

			png_data[pixel_index + 0] = static_cast<channel>(255 * pixel_color.x());
			png_data[pixel_index + 1] = static_cast<channel>(255 * pixel_color.y());
			png_data[pixel_index + 2] = static_cast<channel>(255 * pixel_color.z());

			pixel_index += channel_count;
		}
	}

	std::clog << "\rDone                      \n";

	stbi_write_png(IMAGE_FILEPATH_AND_NAME, image_width, image_height, channel_count, png_data, stride_in_bytes);

	return 0;
}
