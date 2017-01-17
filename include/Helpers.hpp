#ifndef HELPERS_HPP
#define HELPERS_HPP


#include "RandomNumbers.hpp"
#include "../Libraries/glm/glm.hpp"

#define PI 3.14159265f


float DistanceSquared(glm::vec3 v1, glm::vec3 v2);


glm::vec3
RandomInHemisphere(const float e);



glm::vec3
RandomInDisk(void);


glm::vec3
Reflect(glm::vec3 dir, const glm::vec3& n);


bool
Refract(const glm::vec3 dir, const glm::vec3& n, float niOverNt, glm::vec3& refracted);


float
Schlick(float cosine, float ior);


#endif
