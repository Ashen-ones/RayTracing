#include "BvhNode.h"
#include <algorithm>

BVHNode::BVHNode(const vector<shared_ptr<Hittable>>& srcObjects, size_t start, size_t end, double time0, double time1)
{
	auto objects = srcObjects;
	int axis = random_int(0, 2);
	//随机一下对比哪个轴
	auto comparator = (axis == 0) ? &box_x_compare
					: (axis == 1) ? &box_y_compare
					: &box_z_compare;

	size_t object_span = end - start;

	if (object_span == 1)
	{
		//左右节点直接等于物体本身
		left = right = objects[start];
	}
	else if (object_span == 2)
	{
		if (comparator(objects[start], objects[start + 1])) {
			left = objects[start];
			right = objects[start + 1];
		}
		else {
			left = objects[start + 1];
			right = objects[start];
		}
	}
	else
	{
		//实际上等于递归的创建
		std::sort(objects.begin() + start, objects.begin() + end, comparator);
		auto mid = start + object_span / 2;
		left = make_shared<BVHNode>(objects, start, mid, time0, time1);
		right = make_shared<BVHNode>(objects, mid, end, time0, time1);
	}

	AABB box_left, box_right;
	//求这个节点的的包围盒的左侧和右侧
	if (!left->BoundingBox(time0, time1, box_left)
		|| !right->BoundingBox(time0, time1, box_right)
		)
	{
		std::cerr << "No bounding box in bvh_node constructor.\n";
	}
	
	//该节点的包围盒的左侧和右侧加起来就是整个的包围盒大小
	box = surrounding_box(box_left, box_right);
}

//只能求取是否撞到了该物体，如果是True，应该需要绑定回去
bool BVHNode::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	if (!GetBox().Hit(r, t_min, t_max))
	{
		return false;
	}

	bool hitLeft = left->Hit(r, t_min, t_max, rec);
	bool hitRight = right->Hit(r, t_min, t_max, rec);
	return hitLeft || hitRight;
}

bool BVHNode::BoundingBox(double time0, double time1, AABB& output_box) const
{
	output_box = box;
	return true;
}
