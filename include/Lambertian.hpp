#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "Material.hpp"
#include "Helpers.hpp"
#include "RandomNumbers.hpp"
#include "Texture.hpp"
#include "../Libraries/glm/glm.hpp"


class Lambertian : public Material
{
public:
	Lambertian(Texture * a)
		:
		albedo(a)
	{}
	
	Lambertian(glm::vec3 c)
		:
		albedo(new ConstantTexture(c))
	{}
	
	virtual bool
	Scatter(
			const Ray& rayIn, 
			const ShadeRecord& sr, 
			glm::vec3& atten, 
			Ray& rayOut
			) const;
			
	void
	SetTexture(Texture * t) { albedo = t; }
	
private:
	Texture * albedo;

};


#endif
