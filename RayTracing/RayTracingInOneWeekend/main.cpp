#include<iostream>
#include "BvhNode.h"
#include"RTWeekend.h"
#include "color.h"
#include "Sphere.h"
#include "Gluttest.h"
#include "HitTableList.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include <iostream>
#include <thread>
#include "logger.h"
#include "MoveSphere.h"
#include "CheckerTexture.h"
#include "PerlinNoiseTexture.h"
#include "ImageTexture.h"
#include "DiffuseLight.h"
#include "XYRect.h"
#include "YZRect.h"
#include "XZRect.h"
#include "Box.h"
#include "Translate.h"
#include "RotateY.h"
#include "ConstantMedium.h"

using namespace logger;
using namespace std;

int all = 0;
BVHNode worldNode;

Color RayColor(const Ray& r, const Color& background, const HitTableList& world, int depth);
void Process(Gluttest glut, Camera camera, HitTableList world, int depth, int sample, int threadCount, int threadIndex, int ilimit, int jlimit);
HitTableList RandomScene();
HitTableList Scene2();
HitTableList Scene();


int main(int argc, char* argv[])
{
	clock_t start, End;//数据类型是clock_t，需要头文件#include<time.h>
	start = clock();
	const auto aspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
	int depth = 10;
	int sample = 100;
	//eyes

	Gluttest glut = Gluttest(imageWidth, imageHeight,argc,argv);
	glut.GlutInit();
	HitTableList world = Scene();
	worldNode = BVHNode(world, 0, 0);
	End = clock();
	cout << "构建BVH的时间" << (double)(End - start) / CLOCKS_PER_SEC << endl;

	all = imageWidth * imageHeight;

	Point3 lookfrom(278, 278, -800);
	Point3 lookat(278, 278, 0);
	Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	auto vofv = 40;

	Camera camera(lookfrom, lookat, vup, vofv, aspectRatio, aperture, dist_to_focus,0.0,1.0);

	int threadCount = 64;

	vector<std::thread> threadList;
	for (int i=0; i<threadCount;i++)
	{
		threadList.push_back(thread(Process, glut, camera, world, depth, sample, threadCount, i,imageWidth,imageHeight));
	}
	for (auto& a : threadList)
	{
		a.join();
	}
	End = clock();
	cout << "总渲染的时间" << (double)(End - start) / CLOCKS_PER_SEC << endl;
	glut.GlutMainLoop();
}

Color RayColor(const Ray& r,const Color&background, const HitTableList& world, int depth) {

	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	HitRecord rec;

	if (!worldNode.Hit(r, 0.0001, infinity, rec))
	{
		return background;
	}

	Ray scattered;
	Color attenuation;
	Color emitted = rec.materialPtr->Emitted(rec.u, rec.v, rec.p);

	if (!rec.materialPtr->Scatter(r, rec, attenuation, scattered))
	{
		return emitted;
	}

	return emitted + attenuation * RayColor(scattered, background, world, depth - 1);
}

void Process(Gluttest glut, Camera camera, HitTableList world, int depth, int sample, int threadCount, int threadIndex, int ilimit, int jlimit)
{
	//std::cout << "\r index : " << threadIndex << ' ' << " j index" << jlimit - jlimit * threadIndex / threadCount - 1 << endl<<std::flush;

	for (int j = jlimit - jlimit * threadIndex / threadCount - 1; j >= jlimit - jlimit * (threadIndex + 1) / threadCount; --j)
	{
		for (int i = 0; i < ilimit; ++i) {
			{
				Color pixelColor = Color(0, 0, 0);
				for (int k = 0; k < sample; k++)
				{
					auto u = (i + random_double()) / (ilimit - 1);
					auto v = (j + random_double()) / (jlimit - 1);
					Ray r = camera.GetRay(u, v);
					pixelColor += RayColor(r,Color(0,0,0), world, depth);
				}

				auto scale = 1.0 / sample;
				auto r = pixelColor.x();
				auto g = pixelColor.y();
				auto b = pixelColor.z();


				r = sqrt(scale * r);
				g = sqrt(scale * g);
				b = sqrt(scale * b);

				int pos = (j * ilimit + i) * 3;

				Gluttest::PixelBuffer[pos] = clamp(r * 255.999,0,256);
				Gluttest::PixelBuffer[pos + 1] =   clamp(g * 255.999, 0, 256);;
				Gluttest::PixelBuffer[pos + 2] =   clamp(b * 255.999, 0, 256);;

			}
		}
	}
}

HitTableList RandomScene() {
	auto checker = make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
	HitTableList world;
	auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));
	for (int a = -6; a < 2; a++) {
		for (int b = -6; b < 2; b++) {
			auto choose_mat = random_double();
			Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - Point3(4, 0.2, 0)).length() > 0.9 || true) {
				shared_ptr<Material> sphere_material;
				if (choose_mat < 0.8 || true) {
					// diffuse
					auto albedo = Color::random() * Color::random();
					sphere_material = make_shared<Lambertian>(albedo);
					world.Add(make_shared<MoveSphere>(center, Point3(center.x(), center.y() + 0.3, center.z()), 0.0, 1.0, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = Color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<Metal>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}
	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));
	auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.Add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));
	auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

	return world;
}
HitTableList Scene2()
{
	auto earth_texture2 = make_shared<ImageTexture>("D:/AshenOneProject/RayTracing/Source/2.jpg");
	auto perlinNoiseTexture = make_shared<PerlinNoiseTexture>();
	HitTableList world;
	auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Point3(0, 3.0, 0), 1.0, make_shared<DiffuseLight>(Color(0.3, 0.7, 0.9))));
	world.Add(make_shared<Sphere>(Point3(0, 1.0, 0), 0.5,  make_shared<Lambertian>(perlinNoiseTexture)));
	world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(perlinNoiseTexture)));

	return world;
}
HitTableList Scene()
{
	HitTableList world;
	switch (5)
	{
	case 1:
	{
		auto earth_texture2 = make_shared<ImageTexture>("D:/AshenOneProject/RayTracing/Source/2.jpg");
		auto perlinNoiseTexture = make_shared<PerlinNoiseTexture>();
		world.Add(make_shared<Sphere>(Point3(0, 3.0, 0), 1.0, make_shared<DiffuseLight>(Color(0.5, 0.2, 0.5))));
		world.Add(make_shared<Sphere>(Point3(0, 1.0, 0), 0.5, make_shared<Lambertian>(perlinNoiseTexture)));
		world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(perlinNoiseTexture)));
	}
		break;
	case 2:
	{
		auto pertext = make_shared<PerlinNoiseTexture>();
		world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
		world.Add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));
		auto difflight = make_shared<DiffuseLight>(Color(4, 4, 4));
		world.Add(make_shared<XYRect>(3, 5, 1, 3, -2, difflight));
	}
		break;
	case 3:
	{
		auto red = make_shared<Lambertian>(Color(.65, .05, .05));
		auto white = make_shared<Lambertian>(Color(.73, .73, .73));
		auto green = make_shared<Lambertian>(Color(.12, .45, .15));
		auto light = make_shared<DiffuseLight>(Color(15, 15, 15));
		world.Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
		world.Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
		world.Add(make_shared<XZRect>(213, 343, 227, 332, 554, light));
		world.Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
		world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
		world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));
		world.Add(make_shared<Box>(Point3(130, 0, 65), Point3(295, 165, 230), white));
		world.Add(make_shared<Box>(Point3(265, 0, 295), Point3(430, 330, 460), white));
		shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
		box1 = make_shared<RotateY>(box1, 15);
		box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));
		world.Add(box1);

		shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
		box2 = make_shared<RotateY>(box2, -18);
		box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));
		world.Add(box2);

		return world;
	}
	case 4:
	{
		HitTableList boxes1;
		auto ground = make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

		const int boxes_per_side = 20;
		for (int i = 0; i < boxes_per_side; i++) {
			for (int j = 0; j < boxes_per_side; j++) {
				auto w = 100.0;
				auto x0 = -1000.0 + i * w;
				auto z0 = -1000.0 + j * w;
				auto y0 = 0.0;
				auto x1 = x0 + w;
				auto y1 = random_double(1, 101);
				auto z1 = z0 + w;

				boxes1.Add(make_shared<Box>(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
			}
		}

		HitTableList objects;

		objects.Add(make_shared<BVHNode>(boxes1, 0, 1));

		auto light = make_shared<DiffuseLight>(Color(7, 7, 7));
		objects.Add(make_shared<XZRect>(123, 423, 147, 412, 554, light));

		auto center1 = Point3(400, 400, 200);
		auto center2 = center1 + Vec3(30, 0, 0);
		auto moving_sphere_material = make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
		objects.Add(make_shared<MoveSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

		objects.Add(make_shared<Sphere>(Point3(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
		objects.Add(make_shared<Sphere>(
			Color(0, 150, 145), 50, make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)
			));

		auto boundary = make_shared<Sphere>(Point3(360, 150, 145), 70, make_shared<Dielectric>(1.5));
		objects.Add(boundary);
		objects.Add(make_shared<ConstantMedium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
		boundary = make_shared<Sphere>(Point3(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
		objects.Add(make_shared<ConstantMedium>(boundary, .0001, Color(1, 1, 1)));

		auto emat = make_shared<Lambertian>(make_shared<ImageTexture>("D:/AshenOneProject/RayTracing/Source/2.jpg"));
		objects.Add(make_shared<Sphere>(Point3(400, 200, 400), 100, emat));
		auto pertext = make_shared<PerlinNoiseTexture>();
		objects.Add(make_shared<Sphere>(Point3(220, 280, 300), 80, make_shared<Lambertian>(pertext)));

		 HitTableList boxes2;
		auto white = make_shared<Lambertian>(Color(.73, .73, .73));
		int ns = 1000;


		for (int j = 0; j < ns; j++) {
			boxes2.Add(make_shared<Sphere>(Point3::random(0, 165), 10, white));
		}

		objects.Add(make_shared<Translate>(
			make_shared<RotateY>(
				make_shared<BVHNode>(boxes2, 0.0, 1.0), 15),
			Vec3(-100, 270, 395)
			)
		);
		return objects;

	}
	default:
		break;
	case 5:
		auto red = make_shared<Lambertian>(Color(.65, .05, .05));
		auto white = make_shared<Lambertian>(Color(.73, .73, .73));
		auto green = make_shared<Lambertian>(Color(.12, .45, .15));
		auto light = make_shared<DiffuseLight>(Color(7, 7, 7));

		world.Add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
		world.Add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
		world.Add(make_shared<XZRect>(113, 443, 127, 432, 554, light));
		world.Add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
		world.Add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
		world.Add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

		shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
		box1 = make_shared<RotateY>(box1, 15);
		box1 = make_shared<Translate>(box1, Vec3(265, 0, 295));

		shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
		box2 = make_shared<RotateY>(box2, -18);
		box2 = make_shared<Translate>(box2, Vec3(130, 0, 65));

		world.Add(make_shared<ConstantMedium>(box1, 0.01, Color(0, 0, 0)));
		world.Add(make_shared<ConstantMedium>(box2, 0.01, Color(1, 1, 1)));

		break;
	}
	return world;
}

