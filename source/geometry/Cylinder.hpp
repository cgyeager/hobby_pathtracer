#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "GeometricObject.hpp"

class Cylinder : public GeometricObject
{
public:
	Cylinder(glm::vec3 c, float r, float h = 0)
		:
		center(c),
		radius(r),
		height(h),
		infiniteY(false)
	{
		if (h == 0)
		{
			infiniteY = true;
		}
	}

	virtual bool Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const;
	virtual bool BoundingBox(float t0, float t1, AABB& box) const;

private:
	glm::vec3 center;
	float radius;
	float height;
	bool infiniteY;
};

#endif
