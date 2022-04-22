#pragma once
#include "RTWeekend.h"
class Texture {
public:
	virtual Color Value(double u, double v, const Point3& p) const = 0;
};
class SolidColor :public Texture
{
public: 
	SolidColor() {}
	SolidColor(Color c) :colorValue(c) {}
	SolidColor(double red, double green, double blue) :SolidColor(Color(red, green, blue)){}

	virtual Color Value(double u, double v, const Vec3& p)const override
	{
		return colorValue;
	}
public:
	Color colorValue;
};
