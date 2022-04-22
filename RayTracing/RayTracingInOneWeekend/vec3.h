#pragma once
#include <cmath>
#include <iostream>

using namespace std;
using std::sqrt;
using std::fabs;

class Vec3
{
public:
	friend ostream &operator<<(ostream &outstream, const Vec3 &v)
	{
		outstream << "x: " << v.e[0] << "  "
				  << "y: " << v.e[1] << "  "
			      << "z: " << v.e[2] << "  ";
		return outstream;
	}
public:
	Vec3() :e{ 0,0,0 } {}
	Vec3(double e0, double e1, double e2) :e{ e0,e1,e2 } {}
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i)const { return e[i]; }

	Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];//
		return *this;
	}

	Vec3& operator-=(const Vec3& v)
	{
		return *this += -v;
	}

	Vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	Vec3& operator/=(const double t)
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

	inline static Vec3 random() {
		return Vec3(random_double(), random_double(), random_double());
	}

	inline static Vec3 random(double min, double max) {
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}


	inline bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

private:

};

using Point3 = Vec3;
using Color = Vec3;

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	//auto value0 = u + (-v);
	//auto value1 = vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	//return  u + ( - v);
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const double t)
{
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline Vec3 operator*( const double t, const Vec3& u)
{
	return Vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline Vec3 operator/(Vec3 v, double t) {
	return (1 / t) * v;
}
inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

inline double dot(const Vec3& u, const Vec3& v) {	
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 random_in_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline Vec3 RandomUnitVector() {
	return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3& normal) {
	Vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}
inline Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

inline Vec3 random_in_unit_disk() {
	while (true) {
		auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
