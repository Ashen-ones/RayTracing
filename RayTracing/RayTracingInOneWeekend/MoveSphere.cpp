#include "MoveSphere.h"

Point3 MoveSphere::center(double time) const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MoveSphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
	Vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);
	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < tMin || tMax < root) {
		root = (-half_b + sqrtd) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	auto outward_normal = (rec.p - center(r.time())) / radius;
	rec.SetFaceNormal(r, outward_normal);
	rec.materialPtr = materialPtr;
	
	return true;
};

bool MoveSphere::BoundingBox(double time0, double time1, AABB& output_box) const
{
	auto box0 = AABB(center0 - Vec3(radius, radius, radius), center0 + Vec3(radius, radius, radius));
	auto box1 = AABB(center1 - Vec3(radius, radius, radius), center1 + Vec3(radius, radius, radius));
	output_box  = surrounding_box(box0, box1);
	return true;
}

