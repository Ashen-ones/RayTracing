#pragma once
#include "RTWeekend.h"
#include "Hittable.h"
#include "Vec3.h"
class RotateY :
    public Hittable
{
public:
	RotateY(shared_ptr<Hittable> p, double angle):ptr(p)
	{
		auto radians = degrees_to_radians(angle);
		sin_theta = sin(radians);
		cos_theta = cos(radians);
		hasbox = ptr->BoundingBox(0, 1, bbox);

		Point3 min(infinity, infinity, infinity);
		Point3 max(-infinity, -infinity, -infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					auto x = i * bbox.Max().x() + (1 - i) * bbox.Min().x();
					auto y = j * bbox.Max().y() + (1 - j) * bbox.Min().y();
					auto z = k * bbox.Max().z() + (1 - k) * bbox.Min().z();

					auto newx = cos_theta * x + sin_theta * z;
					auto newz = -sin_theta * x + cos_theta * z;

					Vec3 tester(newx, y, newz);

					for (int c = 0; c < 3; c++) {
						min.e[c] = fmin(min[c], tester[c]);
						max.e[c] = fmax(max[c], tester[c]);
					}
				}
			}
		}

		bbox = AABB(min, max);
	}

	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		Point3 origin = r.origin();
		Point3 direction = r.direction();

		origin.e[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
		origin.e[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

		direction.e[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
		direction.e[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

		Ray rotated_r(origin, direction, r.time());

		if (!ptr->Hit(rotated_r, t_min, t_max, rec))
			return false;

		auto p = rec.p;
		auto normal = rec.normal;

		p.e[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
		p.e[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

		normal.e[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
		normal.e[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

		rec.p = p;
		rec.SetFaceNormal(rotated_r, normal);

		return true;
	}

	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override {
		output_box = bbox;
		return hasbox;
	}

public:
	shared_ptr<Hittable> ptr;
	double sin_theta;
	double cos_theta;
	bool hasbox;
	AABB bbox;
};

