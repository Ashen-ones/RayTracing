#include "RTWeekend.h"
#include <iostream>
#include "MathTest.h"
using namespace std;
template<class T>

int length(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}

Vec3 TestAdd(Vec3 &v0,Vec3 &v1)
{
	v0 += v1;
	cout <<v0;
	return v0;
}
Vec3 TestMutiply(Vec3 &v0,double t)
{
	cout << v0 * t;
	return v0 * t;
}

void MathTest()
{
	Vec3 v0 = Vec3();
	Vec3 v1 = Vec3(1, 2, 3);
	Vec3 v2 = Vec3(2, 4, 4);
	TestAdd(v1, v2);
	TestMutiply(v1, 3);
}

void MathMultiply()
{

}
