#include "Texture.hpp"



glm::vec3
SphereCheckers::Value(float u, float v, const glm::vec3& p) const
{
	float freq = 25.f;
	float sines = glm::cos(freq*p.x)*glm::cos(freq*p.z)*glm::sin(p.y);

	if (sines < 0)
	{
		return odd->Value(u, v, p);
	}
	else
	{
		return even->Value(u, v, p);
	}
	/*
	float sines = glm::sin(10.f*p.x)*glm::sin(10.f*p.y)*glm::cos(10.f*p.z);

	if (sines < 0.f)
	{
	return odd->Value(u, v, p);
	}
	else
	{
	return even->Value(u, v, p);
	}
	*/
}



glm::vec3
PlaneCheckers::Value(float u, float v, const glm::vec3& p) const
{
	float size = 2.f;
	float x = p.x;
	float z = p.z;

	int ix = glm::floor(x / size);
	int iz = glm::floor(z / size);

	float fx = x / size - ix;
	float fz = z / size - iz;

	float width = 0.5*0.5 / size;

	if ((ix + iz) % 2 == 0)
	{
		return even->Value(u, v, p);
	}
	else
	{
		return odd->Value(u, v, p);
	}
}