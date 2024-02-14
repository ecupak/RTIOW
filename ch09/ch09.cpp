// Project
#include "vec3.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"


int main()
{
	// World.
	HittableList world;

	world.add(std::make_shared<Sphere>(Point3{ 0.0f, 0.0f, -1.0f }, 0.5f));
	world.add(std::make_shared<Sphere>(Point3{ 0.0f, -100.5f, -1.0f }, 100.0f));
	

	// Camera.
	Camera camera{};
	camera.aspect_ratio_ = 16.0f / 9.0f;
	camera.image_width_ = 400;
	camera.samples_per_pixel_ = 100;
	camera.max_depth_ = 50;


	// Render.
	camera.render(world, IMAGE_FILEPATH_AND_NAME);

	return 0;
}
