#pragma once
#include "RTWeekend.h"
#include "Hittable.h"
class MoveSphere: public Hittable
{
public:
	MoveSphere();
	MoveSphere(Point3 p0,Point3 p1,double t0,double t1,double r,shared_ptr<Material> m):
		center0(p0), center1(p1),time0(t0),time1(t1),radius(r),materialPtr(m){}
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec)const override;
	virtual bool BoundingBox(double time0, double time1, AABB& output_box)const override;
	Point3 center(double time) const ;
private:
	Point3 center0, center1;
	double time0, time1;
	double radius;
	shared_ptr<Material> materialPtr;
};

