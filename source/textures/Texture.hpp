#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../../Libraries/glm/glm.hpp"



class Texture
{
public:
	virtual glm::vec3
	Value(float u, float v, const glm::vec3& p) const = 0;
};



class ConstantTexture : public Texture
{
public:
	ConstantTexture() {}
	ConstantTexture(glm::vec3 c)
		:
		color(c)
	{}
	
	ConstantTexture(float r, float g, float b)
		:
		color(r, g, b)
	{}
	
	virtual glm::vec3
	Value(float u, float v, const glm::vec3& p) const
	{
		return color;
	}

private:
	glm::vec3 color;
};



class SphereCheckers: public Texture
{
public:
	SphereCheckers() {}
	SphereCheckers(Texture * t0, Texture * t1)
		:
		even(t0),
		odd(t1)
	{}
	
	virtual glm::vec3
		Value(float u, float v, const glm::vec3& p) const;
	
private:
	Texture * odd;
	Texture * even;
};




class PlaneCheckers : public Texture
{
public:
	PlaneCheckers() {}
	PlaneCheckers(Texture * t0, Texture * t1)
		:
		even(t0),
		odd(t1)
	{}
	
	virtual glm::vec3
		Value(float u, float v, const glm::vec3& p) const;
	
private:
	Texture * odd;
	Texture * even;
};

#endif
