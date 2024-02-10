#include "RT_Weekend.h"

// STL
#include <iostream>

// Includes
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


using channel = char;

int main()
{
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
			double r = static_cast<double>(x) / (width - 1);
			double g = static_cast<double>(y) / (height - 1);
			double b = 0.0;

			png_data[pixel_index + 0] = static_cast<channel>(255.0 * r);
			png_data[pixel_index + 1] = static_cast<channel>(255.0 * g);
			png_data[pixel_index + 2] = static_cast<channel>(255.0 * b);			

			pixel_index += channel_count;
		}
	}

	std::clog << "\rDone                      \n";

	stbi_write_png("RTIOW.png", width, height, channel_count, png_data, stride_in_bytes);

	return 0;
}
