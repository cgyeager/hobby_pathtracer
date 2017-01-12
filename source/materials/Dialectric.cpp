#include Dialectric.cpp



bool
Dialectric::Scatter(
		const Ray& rayIn, 
		const ShadeRecord& sr, 
		glm::vec3& attenuation, 
		Ray& rayOut) const
{
	glm::vec3 outwardNormal;
	glm::vec3 reflected = Reflect(rayIn.d, sr.normal);
	float niOverNt;
	attenuation = glm::vec3(1.f);
	glm::vec3 refracted;
	float reflectProb;
	float cosine;
	
	if ( glm::dot(rayIn.d, sr.normal) > 0.f )
	{
		outwardNormal = -sr.normal;
		niOverNt = ior;
		cosine = ior*glm::dot(rayIn.d, sr.normal) / glm::length(rayIn.d);
	}
	else
	{
		outwardNormal = sr.normal;
		niOverNt = 1.f/ior;		
		cosine = -glm::dot(rayIn.d, sr.normal) / glm::length(rayIn.d);
	}
	
	if ( Refract(rayIn.d, outwardNormal, niOverNt, refracted) )
	{
		reflectProb = Schlick(cosine, ior);
	}
	else
	{
		rayOut = Ray(sr.hitPoint, reflected, rayIn.time);
		reflectProb = 1.f;
	}
	
	if ( RandomFloat() < reflectProb)
	{
		rayOut = Ray(sr.hitPoint, reflected, rayIn.time);
	}
	else
	{
		rayOut = Ray(sr.hitPoint, refracted, rayIn.time);
	}
	
	return true;
}
