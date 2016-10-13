#pragma once
#include "Program.h"
#include "Transform.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object
{
private:
	std::shared_ptr<Program> program;
	Transform transform;

	std::unique_ptr<VBO> vbo;
	std::unique_ptr<EBO> ebo;
	std::unique_ptr<VAO> vao;

	std::function<void(Object &)> update;
public:
	Object(std::shared_ptr<Program> program);
	Object(std::shared_ptr<Program> program, std::function<void(Object &)> update);
	~Object();

	void Draw();

	Transform & GetTransform();

	inline std::shared_ptr<Program> GetShaderProgram() { return program; }
};

