#include "Disk.hpp"

bool
Disk::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	float temp = glm::dot(center - ray.o, normal) / glm::dot(ray.d, normal);

	glm::vec3 p = ray.o + temp*ray.d;

	if ( (temp < tmax && temp > tmin) && DistanceSquared(center, p) < rSquared)
	{
		sr.t = temp;
		sr.hitPoint = ray.o + sr.t*ray.d;
		sr.normal = normal;
		sr.matPtr = matPtr;

		return true;
	}

	return false;
}



bool
Disk::BoundingBox(float t0, float t1, AABB& box) const
{
	return false;
}
