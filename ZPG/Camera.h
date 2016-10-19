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
	const float SENSITIVITY = 0.05f;
	const float MOVE_STEP = 0.1f;

	const float MAX_PITCH = 89.999f;
	const float MIN_PITCH = -MAX_PITCH;

	glm::vec3 eye;
	glm::vec3 target;
	const glm::vec3 up;

	float fov, aspect, near, far;

	float yaw; // right left
	float pitch; // up down

	// Mouse
	int mouseX, mouseY;

	boost::optional<glm::mat4> viewMatrix;
	boost::optional<glm::mat4> projectionMatrix;
public:
	Camera(int width, int height, float fov, float aspect, float near, float far);

	void Set(const Program * program);
	void Rotate(int x, int y);
	void Move(CameraMove move, bool fast);
	void Move(CameraZoom zoom);

private:
	glm::mat4 CalculateViewMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 CalculateTarget();
};

