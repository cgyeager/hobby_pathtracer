#include "Sphere.hpp"



bool
Sphere::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	glm::vec3 oc =  ray.o - center;
	float a = glm::dot(ray.d, ray.d);
	float b = glm::dot(oc, ray.d);
	float c = glm::dot(oc, oc) - radius*radius;
	float discr = b*b - a*c;
	
	if (discr > 0.0001f)
	{
		float temp = ( -b - glm::sqrt(discr) ) / a;
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = (sr.hitPoint - center) / radius;
			sr.matPtr = matPtr;
			return true;
		}
		
		temp = ( -b + glm::sqrt(discr) ) / a;
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = (sr.hitPoint - center) / radius;
			sr.matPtr = matPtr;
			return true;
		}		
	}
	
	return false;
}



bool 
Sphere::BoundingBox(float t0, float t1, AABB& box) const
{
	box = AABB(center - glm::vec3(radius), center + glm::vec3(radius));
	return true;
}
