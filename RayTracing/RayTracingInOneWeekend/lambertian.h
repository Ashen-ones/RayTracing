#pragma once
#include "Material.h"
#include "Hittable.h"
class Lambertian : public Material
{
public:
	Lambertian(const color& a) : albedo(a) {}

	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override 
	{
		auto scatterDirection = rec.normal + RandomUnitVector();

		// Catch degenerate scatter direction
		if (scatterDirection.near_zero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}
public:
	color albedo;
};

