#ifndef BVH_HPP
#define BVH_HPP

#include "GeometricObject.hpp"
#include "../Libraries/glm/glm.hpp"

static int 
BoxXCompare(const void * a, const void * b)
{
	AABB boxLeft, boxRight;
	GeometricObject * aGeom = *(GeometricObject **)a;
	GeometricObject * bGeom = *(GeometricObject **)b;
	
	if (!aGeom->BoundingBox(0.f, 0.f, boxLeft) || 
		!bGeom->BoundingBox(0.f, 0.f, boxRight))
	{
		printf("No bounding box in bvh Node constructor.\n");
	}
	
	if ( boxLeft.Min().x - boxRight.Min().x < 0.f )
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

static int 
BoxYCompare(const void * a, const void * b)
{
	AABB boxLeft, boxRight;
	GeometricObject * aGeom = *(GeometricObject **)a;
	GeometricObject * bGeom = *(GeometricObject **)b;
	
	if (!aGeom->BoundingBox(0.f, 0.f, boxLeft) || 
		!bGeom->BoundingBox(0.f, 0.f, boxRight))
	{
		printf("No bounding box in bvh Node constructor.\n");
	}
	
	if ( boxLeft.Min().y - boxRight.Min().y < 0.f )
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

static int 
BoxZCompare(const void * a, const void * b)
{
	AABB boxLeft, boxRight;
	GeometricObject * aGeom = *(GeometricObject **)a;
	GeometricObject * bGeom = *(GeometricObject **)b;
	
	if (!aGeom->BoundingBox(0.f, 0.f, boxLeft) || 
		!bGeom->BoundingBox(0.f, 0.f, boxRight))
	{
		printf("No bounding box in bvh Node constructor.\n");
	}
	
	if ( boxLeft.Min().z - boxRight.Min().z < 0.f )
	{
		return -1;
	}
	else
	{
		return 1;
	}
}



class BvhNode : public GeometricObject
{
public:
	BvhNode() {}
	BvhNode(GeometricObject ** list, int n, float time0, time1);
	
	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;
	
private:
	GeometricObject * left;
	GeometricObject * right;
	AABB box;
};



BvhNode(GeometricObject ** list, int n, float time0, time1)
{

	int axis = rand()%3;
	
	if (axis == 0)
	{
		qsort(1, n, sizeof(GeometricObject *), BoxXCompare); 
	}
	else if (axis == 1)
	{
		qsort(1, n, sizeof(GeometricObject *), BoxYCompare); 
	}
	else
	{
		qsort(1, n, sizeof(GeometricObject *), BoxZCompare); 
	}
	
	if (n == 1)
	{
		left = right = list[0];
	}
	else if (n == 2)
	{
		left = list[0];
		right = list[1];
	}
	else
	{
		left = new BvhNode(1, n/2, time0, time1);
		right = new BvhNode(1 + n/2, n - n/2, time0, time1);
	}
	
	AABB boxLeft, boxRight;
	
	if (!left->BoundingBox(time0, time1, boxLeft) ||
		!left->BoundingBox(time0, time1, boxLeft))
	{
		printf("No bounding box in bvh Node constructor.\n");
	}
	
	box = SurroundingBox(boxLeft, boxRight);
}



bool 
BvhNode::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	if (box.Hit(ray, tmin, tmax))
	{
		ShadeRecord leftSr. rightSr;
		
		bool hitLeft = left->Hit(ray, tmin, tmax, leftRect);
		bool hitRight = right->Hit(ray, tmin, tmax, rightRect);
		
		if (hitleft && hitRight)
		{
			if (leftRect.t < rightRect.t)
			{
				sr = leftSr;
			}
			else
			{
				sr = rightSr;
			}
		}
		else if (hitLeft)
		{
			sr = leftSr;
			return true;
		}
		else if (hitRight)
		{
			sr = rightSr;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}



bool 
BvhNode::BoundingBox(float t0, float t1, AABB& box) const
{
	b = box;
	return true;
}



#endif
