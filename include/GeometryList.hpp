#ifndef GEOMETRY_LIST_HPP
#define GEOMETRY_LIST_HPP

#include "GeometricObject.hpp"
#include "Ray.hpp"
#include "AABB.hpp"


AABB SurroundingBox(const AABB& box0, const AABB& box1);


class GeometryList : public GeometricObject
{
public:
	GeometricObject ** list;
	int size;

	GeometryList() {}
	GeometryList(GeometricObject ** l, int n) 
		:
		list(l),
		size(n)
		{}
	
	virtual ~GeometryList() {}
		
	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;
};


#endif