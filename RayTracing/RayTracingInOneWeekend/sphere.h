#pragma once
#include "Hittable.h"
class Sphere:public Hittable
{
public:
	Sphere();
	Sphere(point3 cen, double r, shared_ptr<Material> m) :center(cen), radius(r), mat_ptr(m) {}
	virtual bool Hit(
		const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
public:
	point3 center;
	double radius;
	shared_ptr<Material> mat_ptr;

};

