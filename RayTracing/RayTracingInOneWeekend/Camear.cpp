#include "Camera.h"

Camera::Camera(point3 lookfrom,
	point3 lookat,
	Vec3   vup,
	double vfov, 
	double aspect_ratio,
	double aperture,
	double focus_dist)
{
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta / 2);
	auto viewport_height = 2.0 * h;
	auto viewport_width = aspect_ratio * viewport_height;

	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	origin = lookfrom;
	horizontal = focus_dist * viewport_width * u;
	vertical = focus_dist * viewport_height * v;
	lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

	lens_radius = aperture / 2;
}

Ray Camera::GetRay(double s, double t) const
{
	Vec3 rd = lens_radius * random_in_unit_disk();
	Vec3 offset = u * rd.x() + v * rd.y();
	return Ray(
		origin + offset,
		lowerLeftCorner + s * horizontal + t * vertical - origin - offset
	);
}

