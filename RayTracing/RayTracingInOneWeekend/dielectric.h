#pragma once
#include "material.h"
#include "hittable.h"
class dielectric :public material
{
public:

	dielectric(double index_of_refraction) : ir(index_of_refraction) {}
    bool virtual scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
public:
	double ir; // Index of Refraction
private:
	static double reflectance(double cosine, double ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

