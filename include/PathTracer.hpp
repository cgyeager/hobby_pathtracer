#ifndef PATH_TRACER_HPP
#define PATH_TRACER_HPP

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
#include <string>

#define GAMMA false

#define MIN 0.001f
#define MAX 100000.f
#define MAX_DEPTH 50


class PathTracer
{
public:
	PathTracer(CameraSettings &camSettings,
		unsigned int resolutionWidth,
		unsigned int resolutionHeight,
		unsigned int samplesPerPixel);
	~PathTracer();

	void Render();
	void SaveImageAsPPM(std::string& filename);

private:
	unsigned int nx;
	unsigned int ny;
	unsigned int ns;
	Camera camera;

	glm::vec3 * colorBuffer;
	GeometricObject * world;

	std::vector<GeometricObject *> geometry;
	std::vector<Texture *> textures;
	std::vector<Material *> materials;

	glm::vec3 
	Radiance(const Ray& ray, GeometricObject * world, const int depth);
};

#endif
