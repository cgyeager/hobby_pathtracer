#ifndef DIALECTRIC_HPP
#define DIALECTRIC_HPP

#include "Helpers.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "../Libraries/glm/glm.hpp"

#define AIR 1.003f
#define ICE 1.31f
#define WATER 1.33f
#define ALCOHOL 1.36f
#define GLASS 1.52f
#define DIAMOND 2.42f
#define SILICON 3.48f

class Dialectric : public Material
{
public:
	Dialectric(float ri)
		:
		ior(ri)
	{}
	
	virtual bool
	Scatter(
		const Ray& rayIn, 
		const ShadeRecord& sr, 
		glm::vec3& atten, 
		Ray& rayOut) const;
	
private:
	float ior;

};


#endif
