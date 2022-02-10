#include "HitTableList.h"

HitTableList::HitTableList(shared_ptr<hittable> object)
{
	add(object);
}

void HitTableList::add(shared_ptr<hittable> object)
{
	objects.push_back(object);
}

bool HitTableList::Hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record tempRec;
	bool hitAnything = false;
	auto closetSoFar = t_max;

	for (const auto& object : objects)
	{
		if (object->Hit(r, t_min , closetSoFar, tempRec))
		{
			hitAnything = true;
			closetSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}
