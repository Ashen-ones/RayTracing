#pragma once
#include "Material.h"
#include "Hittable.h"
#include "Texture.h"
#include "vec3.h"
class Lambertian : public Material
{
public:

	Lambertian(const Color& a) : albedo(make_shared<SolidColor>(a)) {}
	Lambertian(shared_ptr<Texture> a) : albedo(a) {}

	virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override 
	{
		auto scatterDirection = rec.normal + RandomUnitVector();
		
		// Catch degenerate scatter direction
		if (scatterDirection.near_zero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection, r_in.time());
		attenuation = albedo->Value(rec.u, rec.v, rec.p);
		return true;
	}
	virtual Color Emitted(double u, double v, const Point3& p) const override { return Color(0, 0, 0); }

public:
	shared_ptr<Texture> albedo;
};

