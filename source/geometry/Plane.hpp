#ifndef PLANE_HPP
#define PLANE_HPP

#include "GeometricObject.hpp"
#include "../Ray.hpp"

#include "../../Libraries/glm/glm.hpp"

class Plane : public GeometricObject
{
public:
	Plane()
		:
		position(0.f),
		normal(0.f, 1.f, 0.f)
	{}
	
	Plane(const glm::vec3& p, const glm::vec3& n)
		:
		position(p),
		normal(n)
	{}

	virtual bool Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	virtual bool BoundingBox(float t0, float t1, AABB& box) const;

private:
	glm::vec3 position;
	glm::vec3 normal;
};



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

#endif
