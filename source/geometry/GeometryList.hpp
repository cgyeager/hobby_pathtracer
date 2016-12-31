#ifndef HITABLE_LIST_HPP
#define HITABLE_LIST_HPP

#include "GeometricObject.hpp"
#include "AABB.hpp"

AABB SurroundingBox(const AABB& box0, const AABB& box1)
{
	glm::vec3 small( 
		ffmin(box0.Min().x, box1.Min().x),
		ffmin(box0.Min().y, box1.Min().y),
		ffmin(box0.Min().z, box1.Min().z)
		);
	glm::vec3 big( 
		ffmin(box0.Max().x, box1.Max().x),
		ffmin(box0.Max().y, box1.Max().y),
		ffmin(box0.Max().z, box1.Max().z)
		);
	return AABB(small, big);
}

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
		
	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;
};



bool 
GeometryList::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	ShadeRecord tempSR = {};
	
	bool hitAnything = false;
	
	double closestHitSoFar = tmax;
	
	for (int i = 0; i < size; i++)
	{
		if ( list[i]->Hit(ray, tmin, closestHitSoFar, tempSR) )
		{
			hitAnything = true;
			closestHitSoFar = tempSR.t;
			sr = tempSR;
		}
	}
	return hitAnything;
}



bool 
GeometryList::BoundingBox(float t0, float t1, AABB& box) const
{
	if (size < 1) return false;
	
	AABB tempBox;
	bool firstTrue = list[0]->BoundingBox(t0, t1, tempBox);
	if (!firstTrue)
	{
		return false;
	}
	else
	{
		box = tempBox;
	}
	
	for (int i = 1; i < size; i++)
	{
		if (list[i]->BoundingBox(t0, t1, tempBox))
		{
			box = SurroundingBox(box, tempBox);
		}
		else
		{
			return false;
		}
	}
	
	return true;
}

#endif
