#pragma once
#include "RTWeekend.h"
#include "HitTableList.h"


class BVHNode : public Hittable
{
public:
	BVHNode()
	{
	}
	BVHNode(const HitTableList&list,double time0,double time1): BVHNode(list.objects,0,list.objects.size(),time0,time1)
	{
	}
	BVHNode(const vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);

	virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
	virtual bool BoundingBox(double time0, double time1, AABB& outputBox)const override;

	AABB GetBox() const { return box;}
	shared_ptr<Hittable> left;
	shared_ptr<Hittable> right;
	AABB box;

};

inline bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) {
	AABB boxA;
	AABB boxB;

	if (!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
		std::cerr << "No bounding box in bvh_node constructor.\n";

	return boxA.Min().e[axis] < boxB.Min().e[axis];
}

inline bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return box_compare(a, b, 0);
}

inline bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return box_compare(a, b, 1);
}

inline bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
	return box_compare(a, b, 2);
}

