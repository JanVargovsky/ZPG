#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Transform::Transform(glm::vec3 position, float angle, glm::vec3 axis, float scale)
	: position(position), angle(angle), axis(axis), scale(scale)
{
}

mat4 Transform::Get() const
{
	// TODO: Add caching with lazy loading

	mat4 transform;

	transform = translate(transform, position);
	transform = rotate(transform, radians(angle), axis);
	transform = glm::scale(transform, vec3(scale));

	return transform;
}
