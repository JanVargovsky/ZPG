#pragma once
#include "IRenderable.h"
#include "Program.h"
#include "Transform.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "ModelBase.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object : public IRenderable
{
private:
	Program *program;
	ModelBase *model;
	Transform transform;

	std::function<void(Object &)> update;
public:
	Object(Program *program, ModelBase *model);
	Object(Program *program, ModelBase *model, std::function<void(Object &)> update);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	Transform & GetTransform();

	inline Program* GetShaderProgram() { return program; }
};
