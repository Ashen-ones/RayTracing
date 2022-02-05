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
	//const = 0  ��ʾ�������治���޸ı���ֵ�������Ǵ��麯��
	virtual bool Hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
};

