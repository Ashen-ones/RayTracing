#pragma once
#include "RTWeekend.h"
#include "Vec3.h"
class Ray
{
public:
	Ray() {};
	Ray(const Point3& origin, const Vec3& direction,double time = 0.0 ) :orig(origin), dir(direction),tm(time){}
	Point3 origin() const { return orig; }
	Vec3 direction()const { return dir; }
	
	Point3 at(double t)const {
		return orig + t * dir;
	}

	double time() const { return tm; };
public:
	Point3 orig;
	Vec3 dir;
	double tm;
};
