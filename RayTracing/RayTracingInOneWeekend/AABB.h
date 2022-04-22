#pragma once
#include "RTWeekend.h"
class AABB
{
public:
	AABB() {}
	AABB(const Point3& a, const Point3& b) {
		minimum = a;
		maximum = b;
	}

	Point3 Min() const { return minimum; }
	Point3 Max() const { return maximum; }

	inline	bool Hit(const Ray& r, double tMin,double TMax)
	{
		for (int a = 0; a < 3; a++) {
			auto invD = 1.0f / r.direction()[a];
			auto t0 = (Min()[a] - r.origin()[a]) * invD;
			auto t1 = (Max()[a] - r.origin()[a]) * invD;

			if (invD < 0.0f)
			{
				std::swap(t0, t1);
			}

			tMin = t0 > tMin ? t0 : tMin;
			TMax = t1 < TMax ? t1 : TMax;
			if (TMax <= tMin)
			{
				return false;
			}

		}
		return true;
	}
	Point3 minimum;
	Point3 maximum;
};

 static AABB surrounding_box(AABB box0, AABB box1) {
	Point3 small(
		fmin(box0.Min().x(), box1.Min().x()),
		fmin(box0.Min().y(), box1.Min().y()),
		fmin(box0.Min().z(), box1.Min().z())
	);

	Point3 big(
		fmax(box0.Max().x(), box1.Max().x()),
		fmax(box0.Max().y(), box1.Max().y()),
		fmax(box0.Max().z(), box1.Max().z())
	);

	return AABB(small, big);
}

