#ifndef MOVING_SPHERE_HPP
#define MOVING_SPHERE_HPP

#include "GeometricObject.hpp"
#include "AABB.hpp"
#include "float.h"


class MovingSphere : public GeometricObject
{
public:

	MovingSphere() 
		:
		center0(0.f),
		center1(0.f, 1.f, 0.f),
		time0(0.f),
		time1(1.f),
		radius(1.f)
	{}

	MovingSphere(glm::vec3 c0, glm::vec3 c1, float t0, float t1, float r)
		:
		center0(c0),
		center1(c1),
		time0(t0),
		time1(t1),
		radius(r)
	{}
	
	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;
	
	glm::vec3 
	Center(float t) const;
	
private:
	glm::vec3 center0, center1;
	float time0, time1;
	float radius;
};


#endif
