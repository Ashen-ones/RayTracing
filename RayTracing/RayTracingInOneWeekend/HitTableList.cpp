#include "HitTableList.h"

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
		if (object->Hit(r, t_min , closetSoFar, tempRec))
		{
			hitAnything = true;
			closetSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}
