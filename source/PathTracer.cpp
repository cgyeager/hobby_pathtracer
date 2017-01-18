#include "PathTracer.hpp"


PathTracer::PathTracer(CameraSettings &camSettings, 
	unsigned int resolutionW = 600, 
	unsigned int resolutionH = 400, 
	unsigned int samplesPerPixel = 16)
	:
	nx(resolutionW),
	ny(resolutionH),
	ns(samplesPerPixel),
	colorBuffer(new glm::vec3[sizeof(glm::vec3) * resolutionW*resolutionH]),
	camera(camSettings)
{	
	textures.push_back( new PlaneCheckers(glm::vec3(0.5f, 0.1f, 0.f), glm::vec3(0.9f, 0.9f, 0.9f)) );
	textures.push_back( new SphereCheckers(glm::vec3(0.1f, 0.1f, 0.25f), glm::vec3(0.9f, 0.9f, 0.9f)) );
	
	materials.push_back( new Lambertian(textures[1]) );
	materials.push_back( new Lambertian(glm::vec3(237.f / 255.f, 181.f / 255.f, 145.f / 255.f)) );

	geometry.push_back(new Sphere(0.f, 0.5f, -1.f, 0.5f));
	geometry[0]->SetMaterial(materials[0]);

	geometry.push_back(new Plane);
	geometry[1]->SetMaterial(materials[1]);

	world = new GeometryList(&geometry[0], geometry.size());
}



PathTracer::~PathTracer()
{
   	delete colorBuffer;
	
	for (int i = 0; i < geometry.size(); i++)
		delete geometry[i];
	
	for (int i = 0; i < textures.size(); i++)
		delete textures[i];

	for (int i = 0; i < materials.size(); i++)
		delete materials[i];

	delete world;
}



void 
PathTracer::Render()
{
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
}



glm::vec3 
PathTracer::Radiance(const Ray& ray, GeometricObject * world, const int depth)
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



void
PathTracer::SaveImageAsPPM(std::string &filename)
{
	SavePPM(filename, colorBuffer, nx, ny, GAMMA);
}