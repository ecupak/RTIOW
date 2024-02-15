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

	std::shared_ptr<Lambertian> material_ground{ std::make_shared<Lambertian>(Color{0.8f, 0.8f, 0.0f}) };
	std::shared_ptr<Lambertian> material_center{ std::make_shared<Lambertian>(Color{0.7f, 0.3f, 0.3f}) };
	std::shared_ptr<Lambertian> material_behind{ std::make_shared<Lambertian>(Color{0.3f, 0.4f, 0.8f}) };
	std::shared_ptr<Dielectric> material_left{ std::make_shared<Dielectric>(1.5f) };
	std::shared_ptr<Metal> material_right{ std::make_shared<Metal>(Color{0.8f, 0.6f, 0.2f}, 0.05f) };

	world.add(std::make_shared<Sphere>(Point3{  0.0f, -100.5f, -1.0f }, 100.0f, material_ground));
	world.add(std::make_shared<Sphere>(Point3{  0.0f,    0.0f, -1.0f },   0.5f, material_center));
    world.add(std::make_shared<Sphere>(Point3{  0.0f,    0.0f,  1.0f },   0.5f, material_behind));
	world.add(std::make_shared<Sphere>(Point3{ -1.0f,    0.0f, -1.0f },  -0.5f, material_left));
	world.add(std::make_shared<Sphere>(Point3{  1.0f,    0.0f, -1.0f },   0.5f, material_right));
	

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
