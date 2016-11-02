#pragma once
#include "IRenderable.h"
#include "Updatable.h"
#include "Program.h"
#include "Transform.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "ModelBase.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object : public Updatable, public IRenderable
{
private:
	int id;
	Program *program;
	ModelBase *model;
	Transform transform;
	boost::optional<glm::vec3> color;
public:
	Object(Program *program, ModelBase *model);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	Transform & GetTransform();

	inline Program* GetShaderProgram() { return program; }
	inline int GetId() { return id; }

	void SetColor(glm::vec3 c) {
		color = c;
	}
};
