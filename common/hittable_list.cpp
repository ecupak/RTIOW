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


const bool HittableList::hit(const Ray& ray, float ray_Tmin, float ray_Tmax, HitRecord& hit_record) const
{
	HitRecord temp_record;
	bool was_anything_hit{ false };
	float closest_hit{ ray_Tmax };

	for (const std::shared_ptr<Hittable>& object : objects_)
	{
		if (object->hit(ray, ray_Tmin, closest_hit, temp_record))
		{
			was_anything_hit = true;
			closest_hit = temp_record.t;
			hit_record = temp_record;
		}
	}

	return was_anything_hit;
}