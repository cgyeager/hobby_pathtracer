#include "AABB.hpp"

bool
AABB::Hit(const Ray& ray, float tmin, float tmax) const
{
	for (int a = 0; a < 3; a++)
	{
		float invD = 1.f / ray.d[a];
		float t0 = ffmin(
			(min[a] - ray.o[a]) / invD,
			(max[a] - ray.o[a]) / invD
		);
		float t1 = ffmax(
			(min[a] - ray.o[a]) / invD,
			(max[a] - ray.o[a]) / invD
		);

		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);

		if (tmax <= tmin)
		{
			return false;
		}
	}
	return true;
}
