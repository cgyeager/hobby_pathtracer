#include "Plane.hpp"

bool 
Plane::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	double temp = glm::dot(position - ray.o, normal) / glm::dot(ray.d, normal);
	
	if (temp < tmax && temp > tmin)
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
Plane::BoundingBox(float t0, float t1, AABB& box) const
{
	return true;
}
