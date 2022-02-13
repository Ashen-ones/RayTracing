#include "Camera.h"

Camera::Camera()
{
		auto aspect_ratio = 16.0/ 9.0;
		auto viewport_height = 2.0;
		auto viewport_width = aspect_ratio * viewport_height;
		auto focal_length = 1.0;

		origin = point3(0, 0, 0);
		horizontal = vec3(viewport_width, 0.0, 0.0);
		vertical = vec3(0.0, viewport_height, 0.0);
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

}

ray Camera::GetRay(double u, double v) const
{
	return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
