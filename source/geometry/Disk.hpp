#ifndef DISK_HPP
#define DISK_HPP

#include "Helpers.hpp"

class Disk : public GeometricObject
{
public:
	Disk() 
		:
		center(0.f),
		normal(0.f, 1.f, 0.f),
		radius(1.f),
		rSquared(1.f)
	{}

	Disk(const glm::vec3& c, const glm::vec3& n, float r)
		:
		center(c),
		normal(n),
		radius(r),
		rSquared(r*r)
	{}

	Disk(
		float cx, float cy, float cz, 
		float nx, float ny, float nz, 
		float r)
		:
		center(cx, cy, cz),
		normal(nx, ny, nz),
		radius(r),
		rSquared(r*r)
	{}

	virtual bool
		Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;

	virtual bool
		BoundingBox(float t0, float t1, AABB& box) const;

private:
	glm::vec3 center;
	glm::vec3 normal;
	float radius;
	float rSquared;
};



#endif
