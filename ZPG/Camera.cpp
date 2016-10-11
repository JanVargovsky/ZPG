#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <iostream>

using namespace std;
using namespace glm;

Camera::Camera(glm::vec3 target, float fov, float aspect, float near, float far)
	: target(target), fov(fov), aspect(aspect), near(near), far(far), mouseX(0), mouseY(0), v(0), h(0)
{
}

void Camera::Set(const Program * program)
{
	program->Use();

	program->Send("viewMatrix", GetViewMatrix());
	program->Send("projectionMatrix", GetProjectionMatrix());

	program->Unuse();
}

void Camera::Rotate(int x, int y)
{
	//v += ((mouseX - x) * ROTATE_STEP);
	//h += ((mouseY - y) * ROTATE_STEP);

	//target.x = cos(v) * sin(h);
	//target.y = sin(v);
	//target.z = cos(v) * cos(h);

	target.x = (mouseX + x) * ROTATE_STEP;
	target.y = -(mouseY + y) * ROTATE_STEP;

	viewMatrix.reset();
}

void Camera::Move(CameraMove move)
{
	switch (move)
	{
	case Forward:
		position.y -= MOVE_STEP;
		break;
	case Back:
		position.y += MOVE_STEP;
		break;
	case Left:
		position.x -= MOVE_STEP;
		break;
	case Right:
		position.x += MOVE_STEP;
		break;
	}

	viewMatrix.reset();
}

mat4 Camera::CalculateViewMatrix()
{
	return lookAt(position, target, vec3(0, 1, 0));
	//return translate(mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
}

mat4 Camera::GetViewMatrix()
{
	if (!viewMatrix)
		viewMatrix = CalculateViewMatrix();

	return viewMatrix.get();
}

mat4 Camera::CalculateProjectionMatrix()
{
	// TODO: Use ratio width/height instead of 4/3
	//45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//return perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

	return perspective(fov, aspect, near, far);
}

mat4 Camera::GetProjectionMatrix()
{
	if (!projectionMatrix)
		projectionMatrix = CalculateProjectionMatrix();

	return projectionMatrix.get();
}
