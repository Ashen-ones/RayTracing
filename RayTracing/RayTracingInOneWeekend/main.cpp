#include<iostream>
#include"RTWeekend.h"
#include "color.h"
#include "sphere.h"
#include "gluttest.h"
#include "HitTableList.h"
#include "Camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"

using namespace std;

color RayColor(const ray& r,const HitTableList& world,int depth) {
	
	if (depth <= 0)
	{
		return color(0, 0, 0);
	}

	hit_record rec;
	if (world.Hit(r, 0.0001, infinity, rec))
	{
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * RayColor(scattered, world, depth - 1);
		}
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1, 1, 1) + t * color(0.6, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
	int depth = 15;
	int sample = 100;
	//eyes
	Camera camera;

	gluttest glut = gluttest(imageWidth, imageHeight,argc,argv);
	glut.GlutInit();
	HitTableList world;
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));

	auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

	world.add(make_shared<sphere>(point3(0.0, -100.5, -5.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -5.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -5.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -5.0), 0.5, material_right));
	world.add(make_shared<sphere>(point3(0.0, 1.0, -5.0), 0.5, material_right));


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
				for (int k =0 ; k < sample; k++)
				{
					auto u = (i + random_double()) / (imageWidth - 1);
					auto v = (j + random_double()) / (imageHeight - 1);
					ray r = camera.GetRay(u, v);
					pixelColor += RayColor(r,world,depth);
				}

				auto scale = 1.0 / sample;
			    auto r =  pixelColor.x();
				auto g =  pixelColor.y();
				auto b =  pixelColor.z();


				r = sqrt(scale * r);
				g = sqrt(scale * g);
				b = sqrt(scale * b);


				int pos = (j * imageWidth + i) * 3;

				gluttest::PixelBuffer[pos] =     r*255.999;
				gluttest::PixelBuffer[pos + 1] = g*255.999;
				gluttest::PixelBuffer[pos + 2] = b*255.999;
			}
		}
	}
	glut.GlutMainLoop();
}