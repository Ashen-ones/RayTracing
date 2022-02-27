#pragma once
#include "RTWeekend.h"

struct HitRecord;
class Material {
public:
	virtual bool Scatter(
		const Ray& rIn, const HitRecord& rec, color& attenuation, Ray& scattered
	) const = 0;
};

