#pragma once
#include "RTWeekend.h"
#include "Material.h"
#include "Hittable.h"
class Metal : public Material {
public:
	Metal(const color& a,double f = 0) : albedo(a) ,fuzz(f){}

	virtual bool Scatter(
		const Ray& rIn, const HitRecord& rec, color& attenuation, Ray& scattered
	) const override {
		Vec3 reflected = reflect(unit_vector(rIn.direction()), rec.normal);
		scattered = Ray(rec.p, reflected+ fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	color albedo;
	double fuzz;
};
