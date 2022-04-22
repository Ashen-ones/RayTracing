#include "HitTableList.h"
#include "BvhNode.h"

HitTableList::HitTableList(shared_ptr<Hittable> object)
{
	Add(object);
}

void HitTableList::Add(shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool HitTableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	auto closetSoFar = t_max;

	for (const auto& object : objects)
	{
		if (object->Hit(r, t_min, closetSoFar, tempRec))
		{
			hitAnything = true;
			closetSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}

bool HitTableList::BoundingBox(double time0, double time1, AABB& output_box) const
{
	if (objects.empty()) return false;

	AABB temp_box;
	bool first_box = true;

	for (const auto& object : objects) {
		if (!object->BoundingBox(time0, time1, temp_box)) return false;
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}
	return true;
}
