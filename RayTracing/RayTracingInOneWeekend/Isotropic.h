#pragma once
#include "Material.h"
#include "RTWeekend.h"
#include "Texture.h"
#include "hittable.h"
class Isotropic :
    public Material
{
public:
	Isotropic(Color c) : albedo(make_shared<SolidColor>(c)) {}
	Isotropic(shared_ptr<Texture> a) : albedo(a) {}

	virtual bool Scatter(
		const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
	) const override {
		scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
		attenuation = albedo->Value(rec.u, rec.v, rec.p);
		return true;
	}

	virtual Color Emitted(double u, double v, const Point3& p) const override
	{
		return Color(0, 0, 0);
	}

public:
	shared_ptr<Texture> albedo;
};

