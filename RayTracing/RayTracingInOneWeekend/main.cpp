#include<iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include <GLFW/glfw3.h>
#include <glut.h>
#include <gl/GL.h>
#include "gluttest.h"


using namespace std;

color RayColor(const ray& r) {
	auto s0 = sphere(point3(0, 0, -1), 0.5);
	auto s1 = sphere(point3(-1, 0, -3), 0.5);
	hit_record hr;
	hit_record hr1;
	//std::cerr << "\rScanlines remaining: " << t << ' ' << std::flush;
	if (s0.Hit(r, -1000, +1000, hr)) {
		auto hitPoint = hr.p;
		vec3 N = hr.normal;
		return 0.5 * (hr.normal + color(1, 1, 1));
	}
	if (s1.Hit(r, -100, +100, hr1)) {
		auto hitPoint = hr1.p;
		vec3 N = hr1.normal;
		return 0.5 * (hr1.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main(int argc, char* argv[])
{
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

	gluttest glut = gluttest(imageWidth, imageHeight,argc,argv);
	glut.GlutInit();

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		for (int i = 0; i < imageWidth; ++i) {
			{
				auto u = double(i) / (imageWidth - 1);
				auto v = double(j) / (imageHeight - 1);
				ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
				color pixelColor = RayColor(r);
				int pos = (j * imageWidth + i) * 3;
				gluttest::PixelBuffer[pos] = pixelColor.x()*255.999;
				gluttest::PixelBuffer[pos + 1] = pixelColor.y()*255.999;
				gluttest::PixelBuffer[pos + 2] = pixelColor.z()*255.999;
			}
		}
	}
	glut.GlutMainLoop();
}