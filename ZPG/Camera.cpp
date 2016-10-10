#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

using namespace std;
using namespace glm;

Camera::Camera(glm::vec3 target, float fov, float aspect, float near, float far)
	: target(target), fov(fov), aspect(aspect), near(near), far(far)
{
}

void Camera::Set(const Program * program)
{
	program->Use();

	program->Send("viewMatrix", GetViewMatrix());
	program->Send("projectionMatrix", GetProjectionMatrix());

	program->Unuse();
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return lookAt(vec3(5,0,5), vec3(0, 0, 0), vec3(0, 1, 0));
	//return translate(mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
}

glm::mat4 Camera::GetViewMatrix()
{
	if (!viewMatrix)
		viewMatrix = CalculateViewMatrix();

	return viewMatrix.get();
}

glm::mat4 Camera::CalculateProjectionMatrix()
{
	// TODO: Use ratio width/height instead of 4/3
	//45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//return perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

	return perspective(fov, aspect, near, far);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (!projectionMatrix)
		projectionMatrix = CalculateProjectionMatrix();

	return projectionMatrix.get();
}
