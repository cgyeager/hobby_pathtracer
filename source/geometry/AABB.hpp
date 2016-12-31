#ifndef AABB_HPP
#define AABB_HPP

#include "../Ray.hpp"

#include "../../Libraries/glm/glm.hpp"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }



class AABB
{
public:
	AABB() {}
	AABB(const glm::vec3& a, const glm::vec3& b) 
		:
		min(a),
		max(b)
	{}
	
	bool
		Hit(const Ray& ray, float tmin, float tmax) const;

	glm::vec3 Min() const { return min; }
	glm::vec3 Max() const { return max; }

private:
	glm::vec3 min;
	glm::vec3 max;
};





#endif
