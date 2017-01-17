#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "GeometricObject.hpp"
#include "AABB.hpp"
#include "Ray.hpp"
#include "../Libraries/glm/glm.hpp"

class Material;

class Sphere : public GeometricObject
{
public:

	Sphere(void)
		:
		center(0.f),
		radius(1.f)
	{}

	Sphere(float x, float y, float z, float r)
		:
		center(x, y, z),
		radius(r)
	{}
	
	Sphere(glm::vec3 c, float r)
		:
		center(c),
		radius(r)
	{}

	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;

private:
	glm::vec3 center;
	float radius;
};



#endif
