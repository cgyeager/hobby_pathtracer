#include "GeometricObject.hpp"
#include "GeometryList.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "MovingSphere.hpp"
#include "Disk.hpp"
#include "Cylinder.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dialectric.hpp"
#include "Texture.hpp"

#include "../Libraries/glm/glm.hpp"
#include "Utility.hpp"
#include "RandomNumbers.hpp"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>

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



int 
main()
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
	
	std::vector<GeometricObject *> geometry;
	std::vector<Texture *> textures;
	std::vector<Material *> materials;
	
	textures.push_back( new PlaneCheckers(glm::vec3(0.5f, 0.1f, 0.f), glm::vec3(0.9f, 0.9f, 0.9f)) );
	textures.push_back( new SphereCheckers(glm::vec3(0.1f, 0.1f, 0.25f), glm::vec3(0.9f, 0.9f, 0.9f)) );
	
	materials.push_back( new Lambertian(textures[1]) );
	materials.push_back( new Lambertian(glm::vec3(237.f / 255.f, 181.f / 255.f, 145.f / 255.f)) );

	geometry.push_back(new Sphere(0.f, 0.5f, -1.f, 0.5f));
	geometry[0]->SetMaterial(materials[0]);

	geometry.push_back(new Plane);
	geometry[1]->SetMaterial(materials[1]);

	GeometricObject * world = new GeometryList(&geometry[0], geometry.size());
	
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

   	delete colorBuffer;
	
	for (int i = 0; i < geometry.size(); i++)
		delete geometry[i];
	
	for (int i = 0; i < textures.size(); i++)
		delete textures[i];

	for (int i = 0; i < materials.size(); i++)
		delete materials[i];

	delete world;

	
	return 0;
}
