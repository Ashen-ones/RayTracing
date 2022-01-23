#pragma once
#include <cmath>
#include <iostream>
using namespace std;
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
	vec3 operator-() const { return vec3(-e[0], e[1], -e[2]); }
	double operator[](int i)const { return e[i]; }

	vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
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

	double length() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	double length_squared() const
	{
		return std::sqrt(this->length());
	}
	double e[3];
private:

};

using point3 = vec3;
using color = vec3;

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u[0]+v[0], u[1] + v[1], u[2] + v[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v)
{
	return u+(-v);
}

inline double dot(const vec3& u, const vec3& v)
{
	return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 operator*(const vec3& u, const double t)
{
	return u * t;
}
