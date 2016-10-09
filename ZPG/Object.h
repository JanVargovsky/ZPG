#pragma once
#include "Shader.h"
#include "Transform.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object
{
private:
	const std::shared_ptr<Shader> shader;
	Transform transform;

	GLuint VBO, EBO, VAO;

	std::function<void(Object &)> update;
public:
	Object(std::shared_ptr<Shader> shader);
	Object(std::shared_ptr<Shader> shader, std::function<void(Object &)> update);
	~Object();

	void Draw();

	Transform & GetTransform();
};

