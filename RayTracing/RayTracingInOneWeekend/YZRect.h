#pragma once
#include "Hittable.h"
class YZRect :
    public Hittable
{
public:
	YZRect() {}
	YZRect(double _y0, double _y1, double _z0, double _z1, double _k,
		shared_ptr<Material> mat)
		: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		auto t = (k - r.origin().x()) / r.direction().x();
		if (t < t_min || t > t_max)
			return false;
		auto y = r.origin().y() + t * r.direction().y();
		auto z = r.origin().z() + t * r.direction().z();
		if (y < y0 || y > y1 || z < z0 || z > z1)
			return false;
		rec.u = (y - y0) / (y1 - y0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		auto outward_normal = Vec3(1, 0, 0);
		rec.SetFaceNormal(r, outward_normal);
		rec.materialPtr = mp;
		rec.p = r.at(t);
		return true;
	}
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override
	{
		output_box = AABB(Point3(k - 0.0001, y0, z0), Point3(k + 0.0001, y1, z1));
		return true;
	}
public:
	shared_ptr<Material> mp;
	double y0, y1, z0, z1, k;
};

