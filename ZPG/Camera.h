#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 center;
	// Position - vec3
	// Up - vec3
	// CenterLook - vec3

	// get::viewMatrix - mat4
public:
	Camera();
	~Camera();
};

