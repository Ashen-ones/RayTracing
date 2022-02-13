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

	//���������滹�Ƿ���
	inline void SetFaceNormal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	//const = 0  ��ʾ�������治���޸ı���ֵ�������Ǵ��麯��
	virtual bool Hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
};

