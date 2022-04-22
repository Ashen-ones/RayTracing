#pragma once
#include "RTWeekend.h"
class PerlinNoise
{
public :
	PerlinNoise()
	{
		randomFloat = new double[point_count];
		for (int i=0;i<point_count;i++)
		{
			randomFloat[i] = random_double();
		}

		perX = PerlinGenPerm();
		perY = PerlinGenPerm();
		perZ = PerlinGenPerm();
	}
	~PerlinNoise()
	{
		delete[] perX;
		delete[] perY;
		delete[] perZ;
		delete[] randomFloat;
	}
	double Noise(const Point3& p) const {
		auto i = static_cast<int>(50 * p.x()) & 255;
		auto j = static_cast<int>(50 * p.y()) & 255;
		auto k = static_cast<int>(50 * p.z()) & 255;

		return randomFloat[perX[i] ^ perY[j] ^ perZ[k]];
	}
public :

private:
	static const int point_count = 256;
	Color color;
	double* randomFloat;
	int* perX;
	int* perY;
	int* perZ;

	static int* PerlinGenPerm()
	{
		auto p = new int[point_count];

		for (int i = 0; i < point_count; i++)
		{
			p[i] = i;
		}
		Permute(p, point_count);
		return p;
	}

	//用于打乱数组的顺序
	static void Permute(int* p, int n)
	{
		for (int i = 0; i < n ;i++)
		{
			int target = random_int(0, i);
			int tmp = p[i];
			p[i] = target;
			p[target] = tmp;
		}
	}
};

