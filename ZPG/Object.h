#pragma once
#include "Program.h"
#include "Transform.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object
{
private:
	std::shared_ptr<Program> program;
	Transform transform;

	GLuint VBO, EBO, VAO;

	std::function<void(Object &)> update;
public:
	Object(std::shared_ptr<Program> program);
	Object(std::shared_ptr<Program> program, std::function<void(Object &)> update);
	~Object();

	void Draw();

	Transform & GetTransform();
};

