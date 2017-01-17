#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "GeometricObject.hpp"
#include "Ray.hpp"
#include "../Libraries/glm/glm.hpp"

class Material
{
public:

	virtual bool
	Scatter(
		const Ray& rayIn, 
		const ShadeRecord& sr, 
		glm::vec3& atten, 
		Ray& scatteredRay) const = 0;
};

#endif
