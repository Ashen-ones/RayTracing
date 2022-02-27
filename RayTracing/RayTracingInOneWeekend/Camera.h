#pragma once
#include "RTWeekend.h"
class Camera
{
public:
	Camera(point3 lookfrom,
		point3 lookat,
		Vec3   vup,
		double vfov, // vertical field-of-view in degrees
		double aspect_ratio,
		double aperture,
		double focus_dist);
	Ray GetRay(double u,double v)const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;

	Vec3 u, v, w;
	double lens_radius;

};

