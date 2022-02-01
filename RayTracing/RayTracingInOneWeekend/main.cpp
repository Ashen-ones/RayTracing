#include<iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
using namespace std;

bool hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	double discriminant = (b * b - 4 * a * c);
	//std::cerr << "\rScanlines remaining: " << discriminant << ' ' << std::flush;
	return discriminant > 0;
}

color RayColor(const ray& r)
{
	if (hit_sphere(point3(0, 0, -1), 0.3, r))
	{
		return color(1, 0, 0);
	}
	//除以长度的坐标 
	vec3 unitDir = unit_vector(r.direction());
	//根据y轴计算一个色彩出来，之后可以直接看效果

	auto t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main()
{
	//void MathTest();
	//MathTest();
	//return 0;

	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
	
	//eyes
	auto viewportHeight = 2.0;
	auto viewWidth = aspectRatio * viewportHeight  ;
	auto focalLength = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewWidth, 0, 0);
	auto vertical = vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	//固定格式
	std::cout<< "P3\n" << imageWidth<<" "<< imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; --j)
	{
		for (int i = 0; i < imageWidth; ++i) {
			{
				auto u = double(i) / (imageWidth - 1);
				auto v = double(j) / (imageHeight - 1);
				ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
				color pixelCoor = RayColor(r);
				//std::cout << pixelCoor<<endl;
				WriteColor(std::cout, pixelCoor);
			}
		}
	}
}