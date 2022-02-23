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
#include "dielectric.h"
#include <iostream>
#include <thread>
#include "logger.h"
using namespace logger;
using namespace std;

int all = 0;
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

void process(gluttest glut , Camera camera ,HitTableList world ,int depth,int sample ,int threadCount ,int threadIndex,int ilimit,int jlimit)
{
	//std::cout << "\r index : " << threadIndex << ' ' << " j index" << jlimit - jlimit * threadIndex / threadCount - 1 << endl<<std::flush;

	for (int j = jlimit - jlimit * threadIndex /threadCount - 1 ;  j >= jlimit - jlimit * ( threadIndex + 1) / threadCount; --j)
	{
		for (int i = 0 ; i < ilimit; ++i) {
			{
				color pixelColor = color(0, 0, 0);
				for (int k = 0; k < sample; k++)
				{
					auto u = (i + random_double()) / (ilimit - 1);
					auto v = (j + random_double()) / (jlimit - 1);
					ray r = camera.GetRay(u, v);
					pixelColor += RayColor(r, world, depth);
				}

				auto scale = 1.0 / sample;
				auto r = pixelColor.x();
				auto g = pixelColor.y();
				auto b = pixelColor.z();


				r = sqrt(scale * r);
				g = sqrt(scale * g);
				b = sqrt(scale * b);

				int pos = (j * ilimit + i) * 3;

				gluttest::PixelBuffer[pos] = r * 255.999;
				gluttest::PixelBuffer[pos + 1] = g * 255.999;
				gluttest::PixelBuffer[pos + 2] = b * 255.999;
				//all - 1;

			}
		}
	}
}

HitTableList random_scene() {
	HitTableList world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


int main(int argc, char* argv[])
{
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 2000;
	const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
	int depth = 10;
	int sample = 400;
	//eyes

	gluttest glut = gluttest(imageWidth, imageHeight,argc,argv);
	glut.GlutInit();
	HitTableList world = random_scene();


	all = imageWidth * imageHeight;
	//auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	//auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	//auto material_left = make_shared<dielectric>(1.5);
	//auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

	//world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	//world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
	//world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	Camera camera(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);


	clock_t start, end;//数据类型是clock_t，需要头文件#include<time.h>
	int threadCount = 64;
	start = clock();
	vector<std::thread> threadList;
	for (int i=0; i<threadCount;i++)
	{
		threadList.push_back(thread(process, glut, camera, world, depth, sample, threadCount, i,imageWidth,imageHeight));
	}
	for (auto& a : threadList)
	{
		a.join();
	}
	end = clock();
	cout << "F1运行时间" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	glut.GlutMainLoop();
}