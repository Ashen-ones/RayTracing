#pragma once
#include "Hittable.h"
class Sphere:public Hittable
{
public:
	Sphere();
	Sphere(Point3 cen, double r, shared_ptr<Material> m) :center(cen), radius(r), materialPtr(m) {}
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override;
	Point3 center;
	double radius;
	shared_ptr<Material> materialPtr;

private:
	static void GetSphereUv(const Point3& p, double& u, double& v) {
		// p: a given point on the sphere of radius one, centered at the origin.
		// u: returned value [0,1] of angle around the Y axis from X=-1.
		// v: returned value [0,1] of angle from Y=-1 to Y=+1.
		//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
		//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
		//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

		auto theta = acos(-p.y());
		auto phi = atan2(-p.z(), p.x()) + pi;

		u = phi / (2 * pi);
		v = theta / pi;
	}

};
