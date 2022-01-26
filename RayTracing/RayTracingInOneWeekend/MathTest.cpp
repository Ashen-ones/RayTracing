#include "vec3.h"
#include <iostream>
#include "MathTest.h"
using namespace std;
template<class T>

int length(T& arr)
{
	return sizeof(arr) / sizeof(arr[0]);
}


vec3 TestAdd(vec3 &v0,vec3 &v1)
{
	v0 += v1;
	cout <<v0;
	return v0;
}
vec3 TestMutiply(vec3 &v0,double t)
{
	cout << v0 * t;
	return v0 * t;
}

void MathTest()
{
	vec3 v0 = vec3();
	vec3 v1 = vec3(1, 2, 3);
	vec3 v2 = vec3(2, 4, 4);
	TestAdd(v1, v2);
	TestMutiply(v1, 3);
}

void MathMultiply()
{

}
