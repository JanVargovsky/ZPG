#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Transform::Transform(glm::vec3 position, float angle, glm::vec3 axis, float scale)
	: position(position), angle(angle), axis(axis), scale(scale)
{
}

mat4 Transform::Get()
{
	if (!matrix)
		CalculateMatrix();

	return matrix.get();
}

void Transform::CalculateMatrix()
{
	matrix = mat4();

	matrix = translate(matrix.get(), position);
	matrix = rotate(matrix.get(), radians(angle), axis);
	matrix = glm::scale(matrix.get(), vec3(scale));
}
