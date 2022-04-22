#pragma once
#include "RTWeekend.h"
class Camera
{
public:
	Camera(Point3 lookfrom,
		Point3 lookat,
		Vec3   vup,
		double vfov, // vertical field-of-view in degrees
		double aspectRatio,
		double aperture,
		double focusDist,
		double _time0 = 0,
		double _time1 = 0);
	Ray GetRay(double u,double v)const;
private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;

	Vec3 u, v, w;
	double lensRadius;
	double time0, time1;

};

