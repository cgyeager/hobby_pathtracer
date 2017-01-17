#include "MovingSphere.hpp"

bool 
MovingSphere::Hit(const Ray& ray, float tmin, float tmax, ShadeRecord& sr) const
{
	glm::vec3 oc = ray.o - Center(ray.time);
	float a = glm::dot(ray.d, ray.d);
	float b = glm::dot(oc, ray.d);
	float c = glm::dot(oc, oc) - radius*radius;
	
	float discr = b*b - a*c;
	
	if (discr > 0.0001f)
	{
		float temp = ( -b - glm::sqrt(discr) ) / a;
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = (sr.hitPoint - Center(ray.time)) / radius;
			sr.matPtr = matPtr;
			return true;
		}
		
		temp = ( -b + glm::sqrt(discr) ) / a;
		if (temp < tmax && temp > tmin)
		{
			sr.t = temp;
			sr.hitPoint = ray.o + sr.t*ray.d;
			sr.normal = (sr.hitPoint - Center(ray.time)) / radius;
			sr.matPtr = matPtr;
			return true;
		}		
	}
	
	return false;
}



bool 
MovingSphere::BoundingBox(float t0, float t1, AABB& box) const
{
	AABB box0 = AABB(Center(t0) - glm::vec3(radius), Center(t0) + glm::vec3(radius));
	AABB box1 = AABB(Center(t1) - glm::vec3(radius), Center(t1) + glm::vec3(radius));
	
	glm::vec3 small( 
		fmin(box0.Min().x, box1.Min().x),
		fmin(box0.Min().y, box1.Min().y),
		fmin(box0.Min().z, box1.Min().z)
		);
	glm::vec3 big( 
		fmin(box0.Max().x, box1.Max().x),
		fmin(box0.Max().y, box1.Max().y),
		fmin(box0.Max().z, box1.Max().z)
		);
	
	box = AABB(small, big);
	
	return true;
}



glm::vec3 
MovingSphere::Center(float time) const
{
	return center0 + ( (time - time0) / (time1 - time0)*(center1 - center0) );
}

