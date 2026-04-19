#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>

//#define DEBUG
#ifdef DEBUG
#include <thread>
#include<chrono>
#endif DEBUG

color ray_color(const ray& r) {
	return color(0, 0, 0);
}

int main() {

	// Image 

	auto aspect_ratio{ 16.0 / 9.0 };
	int image_width{ 400 };

	// Calculate the image height, and ensure that it's at least 1.
	int image_height{ int(image_width / aspect_ratio) };
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera

	auto focal_length{ 1.0 };
	auto viewport_height{ 2.0 };
	auto viewport_width {viewport_height * (double(image_width) / image_height)};
	auto camera_center{ point3(0,0,0) };

	// Calculate the vectors across the horizontal and down the vertical viewport edges
	// y-axis up, x-axis to the right, negative z-axis pointing in viewing direction
	auto viewport_u{ vec3(viewport_width, 0, 0) };
	auto viewport_v{ vec3(0, -viewport_height, 0) };

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u{ viewport_u / image_width };
	auto pixel_delta_v{ viewport_v / image_height };

	// Calculate the location of the upper left pixel.
	auto viewport_upper_left{ camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2 };

	// the pixel grid starts inset from the viewport edges by half the pixel-to-pixel distance
	auto pixel00_loc{viewport_upper_left + 0.5 * (viewport_u + viewport_v)};

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int i{ 0 }; i < image_height; ++i) {
#ifdef DEBUG
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
#endif
		std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
		for (int j{ 0 }; j < image_width; ++j) {
			auto pixel_center{ pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v) };
			auto ray_direction{ pixel_center - camera_center }; //NOT NORMALIZED!!!
			ray r(camera_center, ray_direction);

			color pixel_color{ ray_color(r) };
			write_color(std::cout, pixel_color); //MUST be called to write to file
		}
	}

	std::clog << "\rDone.                        \n";

	return 0;
}