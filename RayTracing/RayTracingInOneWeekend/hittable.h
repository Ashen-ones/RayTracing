#pragma once
#include "ray.h"

class material;

struct hit_record
{
	point3 p;
	vec3 normal;

	shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	//计算是正面还是反面
	inline void SetFaceNormal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	//const = 0  表示函数里面不能修改变量值，并且是纯虚函数
	virtual bool Hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
};

