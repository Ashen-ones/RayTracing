#include "Sphere.h"

Sphere::Sphere()
{

}

bool Sphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec)const
{
	Vec3 oc = r.origin() - center;
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
	Vec3 outwardNormal = (rec.p - center) / radius;
	rec.SetFaceNormal(r, outwardNormal);
	rec.mat_ptr = mat_ptr;
	return true;
}
