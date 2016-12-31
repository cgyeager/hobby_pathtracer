#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"
#include "Helpers.hpp"
#include "../Libraries/glm/glm.hpp"

struct CameraSettings
{
	glm::vec3 origin;
	glm::vec3 lookAt;
	float fov;
	float aspect;
	float focusDistance;
	float aperture;
	float t0;
	float t1;

	void ComputeAspect(float w, float h)
	{
		aspect = w/h;
	}
	
	void ComputeFocusDistance()
	{
		focusDistance = glm::length(origin - lookAt);
	}
};


class Camera
{
public:
	glm::vec3 lowerLeft;
	glm::vec3 horiz;
	glm::vec3 vert;
	glm::vec3 origin;
	Ray ray;
	glm::vec3 u, v, w;
	float lensRadius;
	float time0, time1;

	Camera(const CameraSettings& settings)
		:
		lowerLeft(-2.f, -1.f, -1.f),
		horiz(4.f, 0.f, 0.f),
		vert(0.f, 2.f, 0.f),
		ray(glm::vec3(0.f), glm::vec3(0.f))
	{
		time0 = settings.t0;
		time1 = settings.t1;
		lensRadius = settings.aperture/2.f;
		float theta = settings.fov*PI/180.f;
		float halfH = glm::tan(theta/2.f);
		float halfW = settings.aspect*halfH;
		
		ray.o = origin = settings.origin;
		w = glm::normalize(settings.origin - settings.lookAt);
		u = glm::normalize( glm::cross(glm::vec3(0.f, -1.f, 0.f), w) );
		v = glm::cross( w, u );
		
		lowerLeft = ray.o - halfW*settings.focusDistance*u - halfH*settings.focusDistance*v - settings.focusDistance*w;
		horiz = 2.f*halfW*settings.focusDistance*u;
		vert = 2.f*halfH*settings.focusDistance*v;
	}
	


	void SetRayDirection(Ray& r, float s, float t)
	{
		glm::vec3 rd = lensRadius*RandomInDisk();
		glm::vec3 offset = u*rd.x + v*rd.y;
		float time = time0 + RandomFloat()*(time1 - time0);
		r.o = origin + offset;
		r.d = lowerLeft + horiz*s + vert*t - ray.o;
		r.time = time;
	}
	
	
	
	void SetRayDirection(float s, float t)
	{
		SetRayDirection(this->ray, s, t);
	}
	
};

#endif



/*
	Camera()
		:
		lowerLeft(-2.f, -1.f, -1.f),
		horiz(4.f, 0.f, 0.f),
		vert(0.f, 2.f, 0.f),
		ray(glm::vec3(0.f), glm::vec3(0.f))
	{
	}
*/
/*
	Camera(glm::vec3 lookFrom, glm::vec3 lookAt, float vfov, float aspect, float aperture, float focusDist)
		:
		lowerLeft(-2.f, -1.f, -1.f),
		horiz(4.f, 0.f, 0.f),
		vert(0.f, 2.f, 0.f),
		ray(glm::vec3(0.f), glm::vec3(0.f))
	{
		lensRadius = aperture/2.f;
		float theta = vfov*PI/180.f;
		float halfH = glm::tan(theta/2.f);
		float halfW = aspect*halfH;
		
		ray.o = origin = lookFrom;
		w = glm::normalize(lookFrom - lookAt);
		u = glm::normalize( glm::cross(glm::vec3(0.f, -1.f, 0.f), w) );
		v = glm::cross( w, u );
		
		lowerLeft = ray.o - halfW*focusDist*u - halfH*focusDist*v - focusDist*w;
		horiz = 2.f*halfW*focusDist*u;
		vert = 2.f*halfH*focusDist*v;
	}
*/	
