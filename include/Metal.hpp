#ifndef METAL_HPP
#define METAL_HPP


#include "Material.hpp"
#include "Helpers.hpp"
#include "Ray.hpp"
#include "../Libraries/glm/glm.hpp"

#include "Texture.hpp"

class Metal : public Material
{
public:
	
	Metal(Texture * a, float g = 0.f)
		:
		albedo(a),
		glossiness(g)
	{}
	
	Metal(glm::vec3 c, float g = 0.f)
		:
		albedo(new ConstantTexture(c)),
		glossiness(g)
	{}

	Metal(float r, float g, float b, float gloss = 0.f)
		:
		albedo(new ConstantTexture(glm::vec3(r, g, b))),
		glossiness(gloss)
	{}
	
	virtual bool
	Scatter(
		const Ray& rayIn, 
		const ShadeRecord& sr, 
		glm::vec3& atten, 
		Ray& rayOut) const;
	
	void
	SetTexture(Texture * t) { albedo = t; }
	
private:
	Texture * albedo;
	float glossiness;
		
};


#endif
