#pragma once

#include <glm/vec3.hpp>

class Phong
{
private:
	glm::vec3 ambient;

public:
	Phong(glm::vec3 ambient);
};
