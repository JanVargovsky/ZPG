#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
	:position(position), scale(scale), rotation(rotation)
{
}

mat4 Transform::Get()
{
	if (!matrix)
		CalculateMatrix();

	return matrix.get();
}

void Transform::AddPosition(const glm::vec3 & point, const float angle, const glm::vec3 & axis)
{
	mat4 transform;
	transform = translate(transform, point);
	transform = rotate(transform, radians(angle), axis);
	transform = translate(transform, -point);

	position = vec3(transform * vec4(position, 1));

	matrix.reset();
}

void Transform::CalculateMatrix()
{
	auto result = mat4();

	result = translate(result, position);
	result *= mat4_cast(rotation);
	result = glm::scale(result, vec3(scale));

	matrix = result;
}
