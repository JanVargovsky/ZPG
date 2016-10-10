#pragma once
#include "Program.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <boost/optional.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 center;

	glm::vec3 target;
	float fov, aspect, near, far;

	boost::optional<glm::mat4> viewMatrix;
	boost::optional<glm::mat4> projectionMatrix;
public:
	Camera(glm::vec3 target, float fov, float aspect, float near, float far);

	void Set(const Program * program);

private:
	glm::mat4 CalculateViewMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
	glm::mat4 GetProjectionMatrix();
};

