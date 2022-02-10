#pragma once
#include "hittable.h"
#include<vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class HitTableList : public hittable
{
public:
	HitTableList() {}
	HitTableList(shared_ptr<hittable> object);
	void add(shared_ptr<hittable> object);
	virtual bool Hit(const ray& r, double t_min, double t_max, hit_record& rec)const override;

public:
	std::vector<shared_ptr<hittable>> objects;
};

