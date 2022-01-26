#include<iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
using namespace std;

color RayColor(const ray& r)
{
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