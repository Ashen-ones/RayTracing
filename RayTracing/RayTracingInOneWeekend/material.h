#pragma once
#include "RTWeekend.h"

struct HitRecord;
class Material {
public:
	virtual bool Scatter(
		const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered
	) const = 0;

	virtual Color Emitted(double u, double v, const Point3& p) const = 0;
};

