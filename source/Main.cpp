

#include "Camera.hpp"
#include "PathTracer.hpp"

#define X_RES 600
#define Y_RES 400

int 
main()
{
	CameraSettings camSettings = {};
	camSettings.origin = glm::vec3(-0.5f, 5.5f, -5.1f);
	camSettings.lookAt = glm::vec3(0.f, 0.2f, 0.1f);
	camSettings.fov = 90.f;
	camSettings.ComputeAspect(X_RES, Y_RES);
	camSettings.ComputeFocusDistance();
	camSettings.aperture = 0.075f;
	camSettings.t0 = 0.f;
	camSettings.t1 = 0.5f;

	PathTracer pt(camSettings, X_RES, Y_RES, 16);

	pt.Render();

	std::string file = "test.ppm";
	pt.SaveImageAsPPM(file);
}