#pragma once
#include "Hittable.h"
#include<vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;


class HitTableList : public Hittable
{
public:
	HitTableList() {}
	HitTableList(shared_ptr<Hittable> object);
	void Add(shared_ptr<Hittable> object);
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec)const override;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;


public:
	std::vector<shared_ptr<Hittable>> objects;
};

