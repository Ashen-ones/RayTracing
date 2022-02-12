#pragma once
#include <cmath>
#include <iostream>

using namespace std;
using std::sqrt;
using std::fabs;

class vec3
{
public:
	friend ostream &operator<<(ostream &outstream, const vec3 &v)
	{
		outstream << "x: " << v.e[0] << "  "
				  << "y: " << v.e[1] << "  "
			      << "z: " << v.e[2] << "  ";
		return outstream;
	}
public:
	vec3() :e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) :e{ e0,e1,e2 } {}
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i)const { return e[i]; }

	vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];//
		return *this;
	}

	vec3& operator-=(const vec3& v)
	{
		return *this += -v;
	}

	vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	double length() const
	{
		return std::sqrt(this->length_squared());
	}
	double e[3];

	//inline static double random_double() {
	//	// Returns a random real in [0,1).
	//	return rand() / (RAND_MAX + 1.0);
	//}

	//inline static double random_double(double min, double max) {
	//	// Returns a random real in [min,max).
	//	return min + (max - min) * random_double();
	//}

	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}



private:

};

using point3 = vec3;
using color = vec3;

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v)
{
	//auto value0 = u + (-v);
	//auto value1 = vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	//return  u + ( - v);
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const double t)
{
	return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator*( const double t, const vec3& u)
{
	return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

inline double dot(const vec3& u, const vec3& v) {	
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}
