#ifndef GEOMETRIC_OBJECT_HPP
#define GEOMETRIC_OBJECT_HPP

#include "Ray.hpp"
#include "AABB.hpp"

#include "../Libraries/glm/glm.hpp"

class Material;

struct ShadeRecord
{
	float t;
	glm::vec3 hitPoint;
	glm::vec3 normal;
	Material * matPtr;
};



class GeometricObject
{
public:

	virtual bool 
	Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const {};
	
	virtual bool 
	BoundingBox(float t0, float t1, AABB& box) const {};
	
	void 
	SetMaterial(Material * m) { matPtr = m; }
	
protected:
	Material * matPtr;
};

#endif
