#include "materials\Lambertian.hpp"



bool
Lambertian::Scatter(
	const Ray& rayIn,
	const ShadeRecord& sr,
	glm::vec3& attenuation,
	Ray& rayOut) const
{
	glm::vec3 target = sr.hitPoint + sr.normal + RandomInHemisphere(1.f);
	rayOut = Ray(sr.hitPoint, target - sr.hitPoint, rayIn.time);
	attenuation = albedo->Value(0, 0, sr.hitPoint);
	return true;
}