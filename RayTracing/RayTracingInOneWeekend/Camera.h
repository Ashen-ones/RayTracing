#pragma once
#include "RTWeekend.h"
class Camera
{
public:
	Camera(point3 lookfrom,
		point3 lookat,
		vec3   vup,
		double vfov, // vertical field-of-view in degrees
		double aspect_ratio,
		double aperture,
		double focus_dist);
	ray GetRay(double u,double v)const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;

	vec3 u, v, w;
	double lens_radius;

};

