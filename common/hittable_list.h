#pragma once

// STL
#include <memory>
#include <vector>

// Project
#include "interval.h"
#include "hittable.h"
#include "ray.h"


class HittableList : public Hittable
{
public:
	// Ctors.
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	// Methods.
	void clear();
	void add(std::shared_ptr<Hittable> object);
	const bool hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const override;

private:
	std::vector<std::shared_ptr<Hittable>> objects_;
};