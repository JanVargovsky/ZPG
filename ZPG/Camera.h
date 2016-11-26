#pragma once

#include <vector>
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

	std::vector<std::function<void(Camera*)>> onCameraMove;
public:
	Camera(float fov, float aspect, float near, float far);

	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::vec3 GetEye();

	void Rotate(int x, int y);
	void Move(CameraMove move, bool fast);
	void Move(CameraZoom zoom);

	void OnCameraMove(std::function<void(Camera*)> callback);

private:
	glm::mat4 CalculateViewMatrix();
	glm::mat4 CalculateProjectionMatrix();
	glm::vec3 CalculateTarget();

	void FireOnCameraMove();
};

