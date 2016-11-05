#pragma once
#include "IRenderable.h"
#include "Updatable.h"
#include "Program.h"
#include "Transform.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Model.h"
#include "StaticModelBase.h"

#include <glm/vec3.hpp>
#include <functional>
#include <memory>

class Object : public Updatable, public IRenderable
{
private:
	int id;
	Program *program;
	Model *model;
	// Deprecated
	StaticModelBase *staticModel;
	Transform transform;
	boost::optional<glm::vec3> color;
public:
	Object(Program *program, Model *model);
	// Deprecated
	Object(Program *program, StaticModelBase *staticModel);

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
