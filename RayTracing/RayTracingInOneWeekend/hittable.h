#pragma once
#include "ray.h"

struct hit_record
{
	point3 p;
	vec3 normal;
	double t;
};

class hittable
{
public:
	//const = 0  表示函数里面不能修改变量值，并且是纯虚函数
	virtual bool Hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
};

