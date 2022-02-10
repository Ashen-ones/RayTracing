#pragma once
#include "RTWeekend.h"
class Camera
{
public:
	Camera();
	ray GetRay(double u,double v)const;
private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};

