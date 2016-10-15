#include "CameraFactory.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

shared_ptr<Camera> CameraFactory::Create(CameraType cameraType)
{
	return shared_ptr<Camera>(new Camera(800, 600, radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f));
}