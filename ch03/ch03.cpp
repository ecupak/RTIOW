#include "ch03.h"

// STL
#include <iostream>

// Includes
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Project
#include "vec3.h"
#include "color.h"


int main()
{
	using channel = char;
	
	int width{ 256 };
	int height{ 256 };
	int channel_count{ 3 };
	int stride_in_bytes{ channel_count * width };
	channel* png_data{ new channel[width * height * channel_count] };

	int pixel_index = 0;

	for (int y = 0; y < height; ++y)
	{
		std::clog << "\rScanlines remaining: " << (height - y) << ' ' << std::flush;

		for (int x = 0; x < width; ++x)
		{
			Color pixel_color{
				static_cast<float>(x) / (width - 1),
				static_cast<float>(y) / (height - 1),
				0.0
			};

			png_data[pixel_index + 0] = static_cast<channel>(255.0 * pixel_color.x());
			png_data[pixel_index + 1] = static_cast<channel>(255.0 * pixel_color.y());
			png_data[pixel_index + 2] = static_cast<channel>(255.0 * pixel_color.z());

			pixel_index += channel_count;
		}
	}

	std::clog << "\rDone                      \n";

	stbi_write_png(IMAGE_FILEPATH_AND_NAME, width, height, channel_count, png_data, stride_in_bytes);

	return 0;
}