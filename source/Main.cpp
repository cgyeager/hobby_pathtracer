#include "geometry/GeometricObject.hpp"
#include "geometry/GeometryList.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Plane.hpp"
#include "geometry/MovingSphere.hpp"
#include "geometry/Disk.hpp"
#include "geometry/Cylinder.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "materials/Material.hpp"
#include "materials/Lambertian.hpp"
#include "materials/Metal.hpp"
#include "materials/Dialectric.hpp"
#include "textures/Texture.hpp"

#include "../Libraries/glm/glm.hpp"
#include "Utility.hpp"
#include "RandomNumbers.hpp"

#include <cstdio>
#include <ctime>
#include <cstdlib>

#define GAMMA false

#define MIN 0.001f
#define MAX 100000.f
#define MAX_DEPTH 50



glm::vec3 
Radiance(const Ray& ray, GeometricObject * world, const int depth)
{	
	ShadeRecord sr = {};
	if (world->Hit(ray, MIN, MAX, sr))
	{
		Ray scattered;
		glm::vec3 attenuation;
		
		if (depth < MAX_DEPTH && sr.matPtr->Scatter(ray, sr, attenuation, scattered))
		{
			return attenuation*Radiance(scattered, world, depth + 1);
		}
	}
	
	float t = 0.5f*( (glm::normalize(ray.d)).y + 1.f );
	return (1.f - t)*glm::vec3(1.f) + t*glm::vec3(0.5f, 0.7f, 1.f);
}



int main()
{
	srand(time(0));
	int nx = 600;
	int ny = 400;
	int ns = 16;
	
	glm::vec3 * colorBuffer = new glm::vec3[sizeof(glm::vec3) * nx*ny];
	
	CameraSettings camSettings = {};
	camSettings.origin = glm::vec3(-0.5f, 5.5f, -5.1f);
	camSettings.lookAt = glm::vec3(0.f, 0.2f, 0.1f);
	camSettings.fov = 90.f;
	camSettings.ComputeAspect(nx, ny);
	camSettings.ComputeFocusDistance();
	camSettings.aperture = 0.075f;
	camSettings.t0 = 0.f;
	camSettings.t1 = 0.5f;
	
	Camera camera(camSettings);
	
	GeometricObject * list[3];
	
	Texture * checkered = new PlaneCheckers(new ConstantTexture(0.5f, 0.1f, 0.f), new ConstantTexture(0.9f, 0.9f, 0.9f));
	Texture * sphereCheckers = new SphereCheckers(new ConstantTexture(0.1f, 0.1f, 0.25f), new ConstantTexture(0.9f, 0.9f, 0.9f));
	list[0] = new Sphere(0.f, 0.5f, -1.f, 0.5f);
	list[0]->SetMaterial(new Lambertian(sphereCheckers));

	list[1] = new Plane;
	list[1]->SetMaterial(new Lambertian(glm::vec3(237.f / 255.f, 181.f / 255.f, 145.f / 255.f)));//new Lambertian(new ConstantTexture(glm::vec3(237.f/255.f, 181.f/255.f, 145.f/255.f))));

	list[2] = new Disk(0.f, 15.f, -5.f, 0.f, 0.f, 1.f, 5.f);
	list[2]->SetMaterial(new Metal(0.8f, 0.5f, 0.65f, 0.5f));

	GeometricObject * world = new GeometryList(list, sizeof(list)/sizeof(list[0]));
	
	for (int j = ny-1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			glm::vec3 pixelColor(0.f);
			
			// multi sampling each pixel
			for (int s = 0; s < ns; s++)
			{
			
				float u = float(i + RandomFloat())/float(nx);
				float v = float(j + RandomFloat())/float(ny);
				
				camera.SetRayDirection(u, v);
				
				pixelColor += Radiance(camera.ray, world, 0);
			}

			colorBuffer[j*nx + i] = pixelColor / float(ns);
			
		}
	}
	

	SavePPM("test.ppm", colorBuffer, nx, ny, GAMMA);

    //	delete colorBuffer;
	// just letting OS clean up resources initialized in main
    // since they're used throughout the entire algorithm	
	return 0;
}
