#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Transform
{
private:
	glm::vec3 position;
	float angle;
	glm::vec3 axis;
	float scale;

public:
	Transform(glm::vec3 position = glm::vec3(0), float angle = 0, glm::vec3 axis = glm::vec3(0, 1, 0), float scale = 1);

	glm::mat4 Get() const;

	// TODO: Add transformations
};

