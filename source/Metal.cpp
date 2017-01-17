#include "Metal.hpp"



bool
Metal::Scatter(
	const Ray& rayIn,
	const ShadeRecord& sr,
	glm::vec3& attenuation,
	Ray& rayOut) const
{
	glm::vec3 reflected = Reflect(glm::normalize(rayIn.d), sr.normal);

	rayOut = Ray(sr.hitPoint, reflected + glossiness*RandomInHemisphere(1.f), rayIn.time);
	attenuation = albedo->Value(0.f, 0.f, sr.hitPoint);

	return glm::dot(rayOut.d, sr.normal) > 0.f;
}