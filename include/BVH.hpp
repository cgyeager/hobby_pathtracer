#ifndef BVH_HPP
#define BVH_HPP

#include "GeometricObject.hpp"
#include "../Libraries/glm/glm.hpp"

#include <cstdio>

class BvhNode : public GeometricObject
{
public:
	BvhNode() {}
	BvhNode(GeometricObject ** list, int n, float time0, float time1);
	
	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const;
	
private:
	GeometricObject * left;
	GeometricObject * right;
	AABB box;
};



#endif
