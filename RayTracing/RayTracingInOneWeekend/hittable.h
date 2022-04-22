#pragma once
#include "Ray.h"
#include "AABB.h"
class Material;

struct HitRecord
{
	Point3 p;
	Vec3 normal;

	shared_ptr<Material> materialPtr;
	double t;
	bool front_face;

	//计算是正面还是反面
	inline void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

	double u, v;

};

class Hittable
{
public:
	//const = 0  表示函数里面不能修改变量值，并且是纯虚函数
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec)const = 0;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const = 0;
};

