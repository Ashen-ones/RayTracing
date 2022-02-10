#include<iostream>
#include"RTWeekend.h"
#include "color.h"
#include "sphere.h"
#include "gluttest.h"
#include "HitTableList.h"
#include "Camera.h"

using namespace std;

color RayColor(const ray& r,const HitTableList& world) {

	hit_record rec;
	if (world.Hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
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
	Camera camera;

	gluttest glut = gluttest(imageWidth, imageHeight,argc,argv);
	glut.GlutInit();
	HitTableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			{
				/*	auto u = (i + random_double()) / (imageWidth - 1);
					auto v = (j + random_double()) / (imageHeight - 1);
					ray r = camera.GetRay(u, v);
					color pixelColor = RayColor(r, world);*/
				color pixelColor = color(0, 0, 0);
				for (int k =0 ; k <1000; k++)
				{
					auto u = (i + random_double()) / (imageWidth - 1);
					auto v = (j + random_double()) / (imageHeight - 1);
					ray r = camera.GetRay(u, v);
					pixelColor += RayColor(r,world);
				}
				pixelColor /= 100;

				int pos = (j * imageWidth + i) * 3;
				gluttest::PixelBuffer[pos] = pixelColor.x()*255.999;
				gluttest::PixelBuffer[pos + 1] = pixelColor.y()*255.999;
				gluttest::PixelBuffer[pos + 2] = pixelColor.z()*255.999;
			}
		}
	}
	glut.GlutMainLoop();
}