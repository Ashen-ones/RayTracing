#include "sphere.h"
 bool sphere::Hit(const ray& r, double tMin, double tMax, hit_record& rec)const
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return false;

	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;

	if (root < tMin||root>tMax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < tMin || root>tMax)
		{
			return false;
		}
	}
	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - center) / radius;

	return true;
}