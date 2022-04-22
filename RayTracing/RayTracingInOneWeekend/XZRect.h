#pragma once
#include "Hittable.h"
class XZRect :
    public Hittable
{
public:
	XZRect() {}
	XZRect(double _x0, double _x1, double _y0, double _y1, double _k,
		shared_ptr<Material> mat)
		: x0(_x0), x1(_x1), z0(_y0), z1(_y1), k(_k), mp(mat) {};

	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		auto t = (k - r.origin().y()) / r.direction().y();
		if (t < t_min || t > t_max)
			return false;
		auto x = r.origin().x() + t * r.direction().x();
		auto z = r.origin().z() + t * r.direction().z();
		if (x < x0 || x > x1 || z < z0 || z > z1)
			return false;
		rec.u = (x - x0) / (x1 - x0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		auto outward_normal = Vec3(0, 1, 0);
		rec.SetFaceNormal(r, outward_normal);
		rec.materialPtr = mp;
		rec.p = r.at(t);
		return true;
	}
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override
	{
		output_box = AABB(Point3(x0, k - 0.0001, z0), Point3(x1, k + 0.0001, z1));
		return true;
	}


public:
	shared_ptr<Material> mp;
	double x0, x1, z0, z1, k;
};

