#include "hittable_list.h"

HittableList::HittableList() {}


HittableList::HittableList(std::shared_ptr<Hittable> object)
{
	add(object);
}


void HittableList::clear()
{
	objects_.clear();
}


void HittableList::add(std::shared_ptr<Hittable> object)
{
	objects_.push_back(object);
}


const bool HittableList::hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const
{
	HitRecord temp_record;
	bool was_anything_hit{ false };
	float closest_hit{ ray_t.max_ };

	for (const std::shared_ptr<Hittable>& object : objects_)
	{
		if (object->hit(ray, Interval{ ray_t.min_, closest_hit }, temp_record))
		{
			was_anything_hit = true;
			closest_hit = temp_record.t;
			hit_record = temp_record;
		}
	}

	return was_anything_hit;
}