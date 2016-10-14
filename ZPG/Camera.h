#pragma once
#include "Program.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <boost/optional.hpp>

enum CameraMove {
	Forward,
	Back,
	Left,
	Right,
	Invalid,
};

enum CameraZoom {
	In,
	Out,
};

class Camera
{
private:
	const float ROTATE_STEP = 0.01f;
	const float MOVE_STEP = 0.5f;

	glm::vec3 position = glm::vec3(10,10,10);
	glm::vec3 up;
	glm::vec3 center;

	glm::vec3 target;
	float fov, aspect, near, far;

	// Mouse
	int mouseX, mouseY, v, h;

	boost::optional<glm::mat4> viewMatrix;
	boost::optional<glm::mat4> projectionMatrix;
public:
	Camera(glm::vec3 target, float fov, float aspect, float near, float far);

	void Set(const Program * program);
	void Rotate(int x, int y);
	void Move(CameraMove move);
	void Move(CameraZoom zoom);

private:
	glm::mat4 CalculateViewMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
	glm::mat4 GetProjectionMatrix();
};

