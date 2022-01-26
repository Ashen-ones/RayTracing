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
	auto value0 = u + (-v);
	auto value1 = vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	return  u + ( - v);
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
