#pragma once
#include "material.h"
#include "hittable.h"
class Dielectric :public Material
{
public:

	Dielectric(double index_of_refraction) : ir(index_of_refraction) {}
    bool virtual Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
	virtual Color Emitted(double u, double v, const Point3& p) const override { return Color(0, 0, 0); }
public:
	double ir; // Index of Refraction
private:
	static double Reflectance(double cosine, double ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}


};

