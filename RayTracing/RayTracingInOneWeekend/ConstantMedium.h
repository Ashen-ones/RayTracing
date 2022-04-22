#pragma once
#include "Hittable.h"
#include "RTWeekend.h"
#include "Texture.h"
#include "Isotropic.h"
class ConstantMedium :public Hittable
{
public:
	ConstantMedium(shared_ptr<Hittable> b, double d, shared_ptr<Texture> a)
		: boundary(b),
		NegInvDensity(-1 / d),
		phaseFunction(make_shared<Isotropic>(a))
	{}

	ConstantMedium(shared_ptr<Hittable> b, double d, Color c)
		: boundary(b),
		NegInvDensity(-1 / d),
		phaseFunction(make_shared<Isotropic>(c))
	{}

	virtual bool Hit(
		const Ray& r, double tMin, double tMax, HitRecord& rec) const override
	{
		const bool enableDebug = false;
		const bool debugging = enableDebug && random_double() < 0.00001;
		
		HitRecord rec1, rec2;
		
		if (!boundary->Hit(r, -infinity, infinity, rec1))
			return false;
				
		if (!boundary->Hit(r, rec1.t + 0.0001, infinity, rec2))
			return false;

		if (debugging) std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << '\n';

		if (rec1.t < tMin) rec1.t = tMin;
		if (rec2.t > tMax) rec2.t = tMax;

		if (rec1.t >= rec2.t)
			return false;

		if (rec1.t < 0)
			rec1.t = 0;

		const auto RayLength = r.direction().length();
		const auto DistanceInsideBoundary = (rec2.t - rec1.t) * RayLength;
		const auto HitDistance = NegInvDensity * log(random_double());

		if (HitDistance > DistanceInsideBoundary)
			return false;

		rec.t = rec1.t + HitDistance / RayLength;
		rec.p = r.at(rec.t);

		if (debugging) {
			std::cerr << "hit_distance = " << HitDistance << '\n'
				<< "rec.t = " << rec.t << '\n'
				<< "rec.p = " << rec.p << '\n';
		}

		rec.normal = Vec3(1, 0, 0);  // arbitrary
		rec.front_face = true;     // also arbitrary
		rec.materialPtr = phaseFunction;

		return true;
	}

	virtual bool BoundingBox(double time0, double time1, AABB& output_box) const override {
		return boundary->BoundingBox(time0, time1, output_box);
	}

public:
	shared_ptr<Hittable> boundary;
	shared_ptr<Material> phaseFunction;
	double NegInvDensity;


};

