#include "Cylinder.hpp"

bool 
Cylinder::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	float a = ray.d.x*ray.d.x + ray.d.z*ray.d.z;
	float b = 2.f*(ray.o.x*ray.d.x + ray.o.z*ray.d.z);
	float c = ray.o.x*ray.o.x + ray.o.z*ray.o.z - radius*radius;

	float discr = b*b - 4.f*a*c;
	float denom = 2.f*a;

	float temp = (-b - glm::sqrt(discr)) / denom;
	glm::vec3 p = ray.o + temp*ray.d;

	if (discr > 0.0001f )//&& p.y <= (center.y + height/2.f) && p.y >= (center.y - height/2.f))
	{
		
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = glm::vec3(sr.hitPoint.x, 0.f, sr.hitPoint.z) / radius;
			sr.matPtr = matPtr;
			return true;
		}

		temp = (-b + glm::sqrt(discr)) / denom;
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = glm::vec3(sr.hitPoint.x, 0.f, sr.hitPoint.z) / radius;
			sr.matPtr = matPtr;
			return true;
		}
	}
	return false;
}



bool 
Cylinder::BoundingBox(float t0, float t1, AABB& box) const
{
	return false;
}
