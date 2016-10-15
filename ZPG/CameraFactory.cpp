#include "CameraFactory.h"

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera * CameraFactory::Create(CameraType cameraType)
{
	return new Camera(vec3(0), radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
}
