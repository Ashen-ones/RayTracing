#pragma once
#include "Hittable.h"
class Translate :
    public Hittable{
public:
Translate(shared_ptr<Hittable> p, const Vec3& displacement)
	: ptr(p), offset(displacement) {}

virtual bool Hit(
	const Ray& r, double t_min, double t_max, HitRecord& rec) const override
{

	Ray moved_r(r.origin() - offset, r.direction(), r.time());
	if (!ptr->Hit(moved_r, t_min, t_max, rec))
		return false;

	rec.p += offset;
	rec.SetFaceNormal(moved_r, rec.normal);

	return true;
}

virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override
{
	{
		if (!ptr->BoundingBox(time0, time1, output_box))
			return false;

		output_box = AABB(
			output_box.Min() + offset,
			output_box.Max() + offset);

		return true;
	}
}
	public:
		shared_ptr<Hittable> ptr;
		Vec3 offset;
};
