// Project
#include "vec3.h"
#include "camera.h"
#include "hittable_list.h"
#include "color.h"
#include "material.h"
#include "sphere.h"


int main()
{
	// World.
	HittableList world;

	std::shared_ptr<Lambertian> diff_blue{ std::make_shared<Lambertian>(Color{0.0f, 0.0f, 1.0f}) };
	std::shared_ptr<Lambertian> diff_red{ std::make_shared<Lambertian>(Color{1.0f, 0.0f, 0.0f}) };
	std::shared_ptr<Lambertian> diff_green{ std::make_shared<Lambertian>(Color{0.0f, 1.0f, 0.0f}) };

	std::shared_ptr<Metal> metal_gold{ std::make_shared<Metal>(Color{0.8f, 0.6f, 0.1f}, 0.0f) };
	std::shared_ptr<Metal> gloss_magenta{ std::make_shared<Metal>(Color{0.6f, 0.0f, 0.6f}, 0.5f) };

	std::shared_ptr<Dielectric> glass{ std::make_shared<Dielectric>(1.5f) };


	world.add(std::make_shared<Sphere>(Point3{  0.0f, -100.5f, -1.0f }, 100.0f, diff_green));
	
	world.add(std::make_shared<Sphere>(Point3{ -1.0f, 0.0f, -1.0f }, -0.4f, glass));
	world.add(std::make_shared<Sphere>(Point3{  0.0f, 0.0f, -1.0f },  0.5f, diff_red));
	world.add(std::make_shared<Sphere>(Point3{  1.0f, 0.0f, -1.0f },  0.5f, metal_gold));
	
	

	// Camera.
	Camera camera{};
	camera.aspect_ratio_ = 16.0f / 9.0f;
	camera.image_width_ = 400;
	camera.samples_per_pixel_ = 100;
	camera.max_depth_ = 50;

	camera.field_of_view_v_ = 90.0f;
	//camera.look_from_ = Point3{ -2.0f, 2.0f, 1.0f };
	camera.look_from_ = Point3{ 0.0f, 0.0f, 0.0f };
	camera.look_at_ = Point3{ 0.0f, 0.0f, -1.0f };

	camera.defocus_angle_ = 0.0f;
	camera.focus_distance_ = 3.4;

	// Render.
	camera.render(world, IMAGE_FILEPATH_AND_NAME);

	return 0;
}
