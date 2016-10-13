#pragma once
#include "Program.h"
#include "Transform.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "ModelBase.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object
{
private:
	std::shared_ptr<Program> program;
	std::shared_ptr<ModelBase> model;
	Transform transform;

	std::function<void(Object &)> update;
public:
	Object(std::shared_ptr<Program> program, std::shared_ptr<ModelBase> model);
	Object(std::shared_ptr<Program> program, std::shared_ptr<ModelBase> model, std::function<void(Object &)> update);
	~Object();

	void Draw();

	Transform & GetTransform();

	inline std::shared_ptr<Program> GetShaderProgram() { return program; }
};

