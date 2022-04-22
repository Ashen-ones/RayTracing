#pragma once
#include "RTWeekend.h"
#include "Material.h"
#include "Hittable.h"
class Metal : public Material {
public:
	Metal(const Color& a,double f = 0) : albedo(a) ,fuzz(f){}

	virtual bool Scatter(
		const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered
	) const override {
		Vec3 reflected = reflect(unit_vector(rIn.direction()), rec.normal);
		scattered = Ray(rec.p, reflected+ fuzz * random_in_unit_sphere(),rIn.time());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	virtual Color Emitted(double u, double v, const Point3& p) const override { return Color(0, 0, 0); }

public:
	Color albedo;
	double fuzz;
};
