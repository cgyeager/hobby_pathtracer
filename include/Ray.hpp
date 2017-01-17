#ifndef RAY_HPP
#define RAY_HPP

#include "../Libraries/glm/glm.hpp"

struct Ray
{
	glm::vec3 o;
	glm::vec3 d;
	float time;

	Ray() {}
	Ray(const glm::vec3 origin, const glm::vec3 dir, float t = 0.f)
		:
		o(origin), d(dir), time(t)
	{}
	
	glm::vec3 PointAt(float t) { return o + t*d; }

};

#endif
