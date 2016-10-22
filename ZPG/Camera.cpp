#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>

#include <memory>
#include <iostream>

using namespace std;
using namespace glm;

Camera::Camera(int width, int height, float fov, float aspect, float near, float far)
	: fov(fov), aspect(aspect), near(near), far(far),
	up(vec3(0.f, 1.f, 0.f))
{
	mouseX = 0;
	mouseY = 0;

	yaw = 0.f;
	pitch = MIN_PITCH;

	eye = vec3(0.0f, 8.0f, 0.0f);
	target = CalculateTarget();
}

void Camera::Set(Program * program)
{
	program->Use();

	program->Send("view", GetViewMatrix());
	program->Send("projection", GetProjectionMatrix());

	program->Send("cameraPosition", eye);

	program->Unuse();
}

void Camera::Rotate(int x, int y)
{
	yaw += (x - mouseX) * SENSITIVITY;
	pitch += (mouseY - y) * SENSITIVITY;

	mouseX = x;
	mouseY = y;

	if (pitch > MAX_PITCH)
		pitch = MAX_PITCH;
	else if (pitch < MIN_PITCH)
		pitch = MIN_PITCH;

	target = CalculateTarget();

	viewMatrix.reset();
	FireOnCameraMove();
}

void Camera::Move(CameraMove move, bool fast)
{
	const float STEP = (!fast ? MOVE_STEP : MOVE_STEP * 2);

	if (move == Forward)
		eye += target * STEP;
	if (move == Back)
		eye -= target * STEP;
	if (move == Left)
		eye -= normalize(cross(target, up)) * STEP;
	if (move == Right)
		eye += normalize(cross(target, up)) * STEP;

	viewMatrix.reset();
	FireOnCameraMove();
}

void Camera::Move(CameraZoom zoom)
{
	switch (zoom)
	{
	case In:
		eye.y += MOVE_STEP;
		break;
	case Out:
		eye.y -= MOVE_STEP;
		break;
	}
	viewMatrix.reset();
	FireOnCameraMove();
}

void Camera::OnCameraMove(std::function<void(Camera*)> callback)
{
	onCameraMove.push_back(callback);
}

mat4 Camera::CalculateViewMatrix()
{
	return lookAt(eye, eye + target, up);
}

mat4 Camera::GetViewMatrix()
{
	if (!viewMatrix)
		viewMatrix = CalculateViewMatrix();

	return viewMatrix.get();
}

mat4 Camera::CalculateProjectionMatrix()
{
	return perspective(fov, aspect, near, far);
}

mat4 Camera::GetProjectionMatrix()
{
	if (!projectionMatrix)
		projectionMatrix = CalculateProjectionMatrix();

	return projectionMatrix.get();
}

vec3 Camera::CalculateTarget()
{
	return normalize(vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	));
}

void Camera::FireOnCameraMove()
{
	for (auto &notify : onCameraMove)
		notify(this);
}
