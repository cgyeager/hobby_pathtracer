#include "Helpers.hpp"

float DistanceSquared(glm::vec3 v1, glm::vec3 v2)
{
	float a = v1.x - v2.x;
	float b = v1.y - v2.y;
	float c = v1.z - v2.z;

	return a*a + b*b + c*c;
}



glm::vec3
RandomInHemisphere(const float e)
{
	float x = RandomFloat();
	float y = RandomFloat();
	float cosPhi = glm::cos(2.f*PI * x);
	float sinPhi = glm::sin(2.f*PI * x);
	float cosTheta = glm::pow(1.f - y, 1.f / (e + 1.f));
	float sinTheta = glm::sqrt(1.f - cosTheta*cosTheta);
	float pu = sinTheta*cosPhi;
	float pv = sinTheta*sinPhi;
	float pw = cosTheta;

	return glm::vec3(pu, pv, pw);
}



glm::vec3
RandomInDisk(void)
{
	float r, phi;
	glm::vec2 sp;

	sp.x = 2.f * RandomFloat() - 1.f;
	sp.y = 2.f * RandomFloat() - 1.f;

	if (sp.x > -sp.y)
	{
		if (sp.x > sp.y)
		{
			r = sp.x;
			phi = sp.y / sp.x;
		}
		else
		{
			r = sp.y;
			phi = 2.f - (sp.x / sp.y);
		}
	}
	else
	{
		if (sp.x < sp.y)
		{
			r = -sp.x;
			phi = 4.f + sp.y / sp.x;
		}
		else
		{
			r = -sp.y;
			if (sp.y != 0.f)
			{
				phi = 6.f - (sp.x / sp.y);
			}
			else
			{
				phi = 0.f;
			}
		}
	}

	phi *= PI / 4.f;

	return glm::vec3(r*glm::cos(phi), r*glm::sin(phi), 0.f);
}



glm::vec3
Reflect(glm::vec3 dir, const glm::vec3& n)
{
	return (dir - 2.f*glm::dot(dir, n)*n);
}



bool
Refract(const glm::vec3 dir, const glm::vec3& n, float niOverNt, glm::vec3& refracted)
{
	glm::vec3 uv = glm::normalize(dir);
	float dt = glm::dot(uv, n);

	float discr = 1.f - niOverNt*niOverNt*(1.f - dt*dt);
	if (discr > 0.f)
	{
		refracted = niOverNt*(uv - n*dt) - n*glm::sqrt(discr);
		return true;
	}
	else
	{
		return false;
	}
}



float
Schlick(float cosine, float ior)
{
	float r0 = (1.f - ior) / (1 + ior);
	r0 = r0*r0;
	return r0 + (1 - r0)*glm::pow((1.f - cosine), 5.f);
}
