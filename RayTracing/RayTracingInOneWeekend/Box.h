#pragma once
#include "Hittable.h"
#include "XYRect.h"
#include "YZRect.h"
#include "XZRect.h"
#include "HitTableList.h"
class Box :
    public Hittable
{
	public:
    Box() {}
    Box(const Point3& p0, const Point3& p1, shared_ptr<Material> ptr) {
		boxMin = p0;
		boxMax = p1;
		sides.Add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
		sides.Add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
		sides.Add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
		sides.Add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
		sides.Add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
		sides.Add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
    }
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		return sides.Hit(r, t_min, t_max, rec);
	}
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override {
		output_box = AABB(boxMin, boxMax);
		return true;
	}

public :
    Point3 boxMin;
    Point3 boxMax;
    HitTableList sides;
};

