#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../Libraries/glm/glm.hpp"



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
	SphereCheckers() 
	
	{}
	SphereCheckers(glm::vec3 e, glm::vec3 o)
		:
		even(new ConstantTexture(e.r, e.g, e.b)),
		odd(new ConstantTexture(o.r, o.g, o.b))
	{}
	
	~SphereCheckers()
	{
		if (odd)
			delete odd;
		if (even)
			delete even;
	}
	
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
	PlaneCheckers(glm::vec3 e, glm::vec3 o)
		:
		even(new ConstantTexture(e.r, e.g, e.b)),
		odd(new ConstantTexture(o.r, o.g, o.b))
	{}

	~PlaneCheckers()
	{
		if (odd)
			delete odd;
		if (even)
			delete even;
	}
	
	virtual glm::vec3
		Value(float u, float v, const glm::vec3& p) const;
	
private:
	Texture * odd;
	Texture * even;
};

#endif
