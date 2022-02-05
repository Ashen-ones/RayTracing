#pragma once
#include "hittable.h"
class sphere:hittable
{
public:
	sphere() {}
	sphere(point3 cen, double r) :center(cen), radius(r) {}
	virtual bool Hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
	point3 center;
	double radius;

};

